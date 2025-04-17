//
// Copyright 2015 gRPC authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#include "src/core/lib/surface/channel_create.h"

#include <grpc/grpc.h>
#include <grpc/impl/channel_arg_names.h>
#include <grpc/support/port_platform.h>

#include "absl/log/check.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_split.h"
#include "src/core/channelz/channelz.h"
#include "src/core/client_channel/client_channel.h"
#include "src/core/client_channel/direct_channel.h"
#include "src/core/config/core_configuration.h"
#include "src/core/credentials/transport/transport_credentials.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/channel/channel_args_preconditioning.h"
#include "src/core/lib/experiments/experiments.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/surface/channel.h"
#include "src/core/lib/surface/channel_stack_type.h"
#include "src/core/lib/surface/lame_client.h"
#include "src/core/lib/surface/legacy_channel.h"
#include "src/core/telemetry/stats.h"
#include "src/core/telemetry/stats_data.h"
#include "src/core/transport/endpoint_transport.h"

namespace grpc_core {

absl::StatusOr<RefCountedPtr<Channel>> ChannelCreate(
    std::string target, ChannelArgs args,
    grpc_channel_stack_type channel_stack_type, Transport* optional_transport) {
  global_stats().IncrementClientChannelsCreated();
  // For client channels, canonify target string and add channel arg.
  // Note: We don't do this for direct channels or lame channels.
  if (channel_stack_type == GRPC_CLIENT_CHANNEL) {
    target =
        CoreConfiguration::Get().resolver_registry().AddDefaultPrefixIfNeeded(
            target);
    args = args.Set(GRPC_ARG_SERVER_URI, target);
  }
  // Set default authority if needed.
  if (!args.GetString(GRPC_ARG_DEFAULT_AUTHORITY).has_value()) {
    auto ssl_override = args.GetString(GRPC_SSL_TARGET_NAME_OVERRIDE_ARG);
    if (ssl_override.has_value()) {
      args = args.Set(GRPC_ARG_DEFAULT_AUTHORITY,
                      std::string(ssl_override.value()));
    }
  }
  // Check whether channelz is enabled.
  if (args.GetBool(GRPC_ARG_ENABLE_CHANNELZ)
          .value_or(GRPC_ENABLE_CHANNELZ_DEFAULT)) {
    // Get parameters needed to create the channelz node.
    const size_t channel_tracer_max_memory = std::max(
        0, args.GetInt(GRPC_ARG_MAX_CHANNEL_TRACE_EVENT_MEMORY_PER_NODE)
               .value_or(GRPC_MAX_CHANNEL_TRACE_EVENT_MEMORY_PER_NODE_DEFAULT));
    const bool is_internal_channel =
        args.GetBool(GRPC_ARG_CHANNELZ_IS_INTERNAL_CHANNEL).value_or(false);
    // Create the channelz node.
    std::string channelz_node_target{target.empty() ? "unknown" : target};
    auto channelz_node = MakeRefCounted<channelz::ChannelNode>(
        channelz_node_target, channel_tracer_max_memory, is_internal_channel);
    channelz_node->AddTraceEvent(
        channelz::ChannelTrace::Severity::Info,
        grpc_slice_from_static_string("Channel created"));
    channelz_node->SetChannelArgs(args);
    // Add channelz node to channel args.
    // We remove the is_internal_channel arg, since we no longer need it.
    args = args.Remove(GRPC_ARG_CHANNELZ_IS_INTERNAL_CHANNEL)
               .SetObject<channelz::BaseNode>(channelz_node)
               .SetObject(channelz_node);
  }
  // Add transport to args.
  if (optional_transport != nullptr) {
    args = args.SetObject(optional_transport);
  }
  // Delegate to appropriate channel impl.
  if (!args.GetBool(GRPC_ARG_USE_V3_STACK).value_or(false)) {
    return LegacyChannel::Create(std::move(target), std::move(args),
                                 channel_stack_type);
  }
  switch (channel_stack_type) {
    case GRPC_CLIENT_CHANNEL:
      return ClientChannel::Create(std::move(target), std::move(args));
    case GRPC_CLIENT_DIRECT_CHANNEL:
      return DirectChannel::Create(std::move(target), args);
    default:
      Crash(absl::StrCat("Invalid channel stack type for ChannelCreate: ",
                         grpc_channel_stack_type_string(channel_stack_type)));
  }
}

namespace {
absl::StatusOr<grpc_channel*> CreateClientEndpointChannel(
    const char* target, grpc_channel_credentials* creds,
    const grpc_channel_args* c_args) {
  const auto& c = CoreConfiguration::Get();
  if (target == nullptr) {
    return absl::InternalError("channel target is NULL");
  }
  if (creds == nullptr) return absl::InternalError("No credentials provided");
  auto args = creds->update_arguments(c.channel_args_preconditioning()
                                          .PreconditionChannelArgs(c_args)
                                          .SetObject(creds->Ref()));
  std::vector<absl::string_view> transport_preferences = absl::StrSplit(
      args.GetString(GRPC_ARG_PREFERRED_TRANSPORT_PROTOCOLS).value_or("h2"),
      ',');
  if (transport_preferences.size() != 1) {
    return absl::InternalError(absl::StrCat(
        "Only one preferred transport name is currently supported: requested='",
        *args.GetOwnedString(GRPC_ARG_PREFERRED_TRANSPORT_PROTOCOLS), "'"));
  }
  auto* transport =
      c.endpoint_transport_registry().GetTransport(transport_preferences[0]);
  if (transport == nullptr) {
    return absl::InternalError(
        absl::StrCat("Unknown transport '", transport_preferences[0], "'"));
  }
  return transport->ChannelCreate(target, args);
}

}  // namespace
}  // namespace grpc_core

grpc_channel* grpc_lame_client_channel_create(const char* target,
                                              grpc_status_code error_code,
                                              const char* error_message) {
  grpc_core::ExecCtx exec_ctx;
  GRPC_TRACE_LOG(api, INFO)
      << "grpc_lame_client_channel_create(target=" << target
      << ", error_code=" << (int)error_code
      << ", error_message=" << error_message << ")";
  if (error_code == GRPC_STATUS_OK) error_code = GRPC_STATUS_UNKNOWN;
  grpc_core::ChannelArgs args =
      grpc_core::CoreConfiguration::Get()
          .channel_args_preconditioning()
          .PreconditionChannelArgs(nullptr)
          .Set(GRPC_ARG_LAME_FILTER_ERROR,
               grpc_core::ChannelArgs::Pointer(
                   new absl::Status(static_cast<absl::StatusCode>(error_code),
                                    error_message),
                   &grpc_core::kLameFilterErrorArgVtable));
  auto channel =
      grpc_core::ChannelCreate(target == nullptr ? "" : target, std::move(args),
                               GRPC_CLIENT_LAME_CHANNEL, nullptr);
  CHECK(channel.ok());
  return channel->release()->c_ptr();
}

// Create a client channel:
//   Asynchronously: - resolve target
//                   - connect to it (trying alternatives as presented)
//                   - perform handshakes
grpc_channel* grpc_channel_create(const char* target,
                                  grpc_channel_credentials* creds,
                                  const grpc_channel_args* c_args) {
  grpc_core::ExecCtx exec_ctx;
  GRPC_TRACE_LOG(api, INFO)
      << "grpc_channel_create(target=" << target << ", creds=" << (void*)creds
      << ", args=" << (void*)c_args << ")";
  auto r = grpc_core::CreateClientEndpointChannel(target, creds, c_args);
  if (!r.ok()) {
    return grpc_lame_client_channel_create(
        target, static_cast<grpc_status_code>(r.status().code()),
        absl::StrCat("Failed to create channel to '", target,
                     "':", r.status().message())
            .c_str());
  }
  return *r;
}
