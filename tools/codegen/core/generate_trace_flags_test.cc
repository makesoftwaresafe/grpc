// Copyright 2025 gRPC authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law of an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "tools/codegen/core/generate_trace_flags.h"

#include <string>

#include "gtest/gtest.h"
#include "absl/strings/string_view.h"

namespace grpc_generator {
namespace testing {

const absl::string_view kInputYaml =
    "tools/codegen/core/generate_trace_flags_test_input.yaml";

TEST(GenerateTraceFlagsTest, GenerateHeader) {
  absl::string_view expected_output =
      R"(// Copyright 2024 gRPC authors.
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
// Automatically generated by tools/codegen/core/gen_trace_flags.py
//

#ifndef GRPC_SRC_CORE_LIB_DEBUG_TRACE_FLAGS_H
#define GRPC_SRC_CORE_LIB_DEBUG_TRACE_FLAGS_H

#include "src/core/lib/debug/trace_impl.h"

namespace grpc_core {

extern DebugOnlyTraceFlag auth_context_refcount_trace;
extern DebugOnlyTraceFlag call_combiner_trace;
extern DebugOnlyTraceFlag call_refcount_trace;
extern DebugOnlyTraceFlag call_state_trace;
extern DebugOnlyTraceFlag chttp2_server_refcount_trace;
extern DebugOnlyTraceFlag closure_trace;
extern DebugOnlyTraceFlag combiner_trace;
extern DebugOnlyTraceFlag cq_refcount_trace;
extern DebugOnlyTraceFlag error_refcount_trace;
extern DebugOnlyTraceFlag fd_refcount_trace;
extern DebugOnlyTraceFlag fd_trace_trace;
extern DebugOnlyTraceFlag lb_policy_refcount_trace;
extern DebugOnlyTraceFlag party_state_trace;
extern DebugOnlyTraceFlag pending_tags_trace;
extern DebugOnlyTraceFlag http2_ph2_transport_trace;
extern DebugOnlyTraceFlag polling_trace;
extern DebugOnlyTraceFlag polling_api_trace;
extern DebugOnlyTraceFlag promise_primitives_trace;
extern DebugOnlyTraceFlag resolver_refcount_trace;
extern DebugOnlyTraceFlag security_connector_refcount_trace;
extern DebugOnlyTraceFlag slice_refcount_trace;
extern DebugOnlyTraceFlag stream_refcount_trace;
extern DebugOnlyTraceFlag subchannel_refcount_trace;
extern DebugOnlyTraceFlag work_serializer_trace;
extern DebugOnlyTraceFlag ztrace_trace;
extern TraceFlag api_trace;
extern TraceFlag apple_polling_trace;
extern TraceFlag backend_metric_trace;
extern TraceFlag backend_metric_filter_trace;
extern TraceFlag bdp_estimator_trace;
extern TraceFlag call_trace;
extern TraceFlag call_error_trace;
extern TraceFlag cares_address_sorting_trace;
extern TraceFlag cares_resolver_trace;
extern TraceFlag cds_lb_trace;
extern TraceFlag channel_trace;
extern TraceFlag channel_stack_trace;
extern TraceFlag chaotic_good_trace;
extern TraceFlag chttp2_hpack_parser_trace;
extern TraceFlag chttp2_new_stream_trace;
extern TraceFlag client_channel_trace;
extern TraceFlag client_channel_call_trace;
extern TraceFlag client_channel_lb_call_trace;
extern TraceFlag client_idle_filter_trace;
extern TraceFlag compression_trace;
extern TraceFlag connectivity_state_trace;
extern TraceFlag dns_resolver_trace;
extern TraceFlag environment_autodetect_trace;
extern TraceFlag event_engine_trace;
extern TraceFlag event_engine_client_channel_resolver_trace;
extern TraceFlag event_engine_dns_trace;
extern TraceFlag event_engine_endpoint_trace;
extern TraceFlag event_engine_endpoint_data_trace;
extern TraceFlag event_engine_poller_trace;
extern TraceFlag fault_injection_filter_trace;
extern TraceFlag flowctl_trace;
extern TraceFlag fork_trace;
extern TraceFlag fuzzing_ee_timers_trace;
extern TraceFlag fuzzing_ee_writes_trace;
extern TraceFlag glb_trace;
extern TraceFlag grpc_authz_api_trace;
extern TraceFlag handshaker_trace;
extern TraceFlag health_check_client_trace;
extern TraceFlag http_trace;
extern TraceFlag http1_trace;
extern TraceFlag http2_ping_trace;
extern TraceFlag http2_stream_state_trace;
extern TraceFlag http_keepalive_trace;
extern TraceFlag inproc_trace;
extern TraceFlag metadata_query_trace;
extern TraceFlag op_failure_trace;
extern TraceFlag orca_client_trace;
extern TraceFlag outlier_detection_lb_trace;
extern TraceFlag pick_first_trace;
extern TraceFlag plugin_credentials_trace;
extern TraceFlag priority_lb_trace;
extern TraceFlag queue_pluck_trace;
extern TraceFlag resource_quota_trace;
extern TraceFlag retry_trace;
extern TraceFlag ring_hash_lb_trace;
extern TraceFlag rls_lb_trace;
extern TraceFlag round_robin_trace;
extern TraceFlag secure_endpoint_trace;
extern TraceFlag server_channel_trace;
extern TraceFlag stateful_session_filter_trace;
extern TraceFlag subchannel_trace;
extern TraceFlag subchannel_pool_trace;
extern TraceFlag tcp_trace;
extern TraceFlag timer_trace;
extern TraceFlag timer_check_trace;
extern TraceFlag token_fetcher_credentials_trace;
extern TraceFlag tsi_trace;
extern TraceFlag weighted_round_robin_lb_trace;
extern TraceFlag weighted_target_lb_trace;
extern TraceFlag xds_client_trace;
extern TraceFlag xds_client_refcount_trace;
extern TraceFlag xds_cluster_impl_lb_trace;
extern TraceFlag xds_cluster_manager_lb_trace;
extern TraceFlag xds_override_host_lb_trace;
extern TraceFlag xds_resolver_trace;
extern TraceFlag xds_server_config_fetcher_trace;
extern TraceFlag xds_wrr_locality_lb_trace;

}  // namespace grpc_core

#endif  // GRPC_SRC_CORE_LIB_DEBUG_TRACE_FLAGS_H
)";
  EXPECT_EQ(GenerateHeader({std::string(kInputYaml)}), expected_output);
}

TEST(GenerateTraceFlagsTest, GenerateCpp) {
  absl::string_view expected_output =
      R"(// Copyright 2024 gRPC authors.
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
// Automatically generated by tools/codegen/core/gen_trace_flags.py
//

#include "src/core/lib/debug/trace.h"
#include "src/core/util/no_destruct.h"

namespace grpc_core {

DebugOnlyTraceFlag auth_context_refcount_trace(false, "auth_context_refcount");
DebugOnlyTraceFlag call_combiner_trace(false, "call_combiner");
DebugOnlyTraceFlag call_refcount_trace(false, "call_refcount");
DebugOnlyTraceFlag call_state_trace(false, "call_state");
DebugOnlyTraceFlag chttp2_server_refcount_trace(false, "chttp2_server_refcount");
DebugOnlyTraceFlag closure_trace(false, "closure");
DebugOnlyTraceFlag combiner_trace(false, "combiner");
DebugOnlyTraceFlag cq_refcount_trace(false, "cq_refcount");
DebugOnlyTraceFlag error_refcount_trace(false, "error_refcount");
DebugOnlyTraceFlag fd_refcount_trace(false, "fd_refcount");
DebugOnlyTraceFlag fd_trace_trace(false, "fd_trace");
DebugOnlyTraceFlag lb_policy_refcount_trace(false, "lb_policy_refcount");
DebugOnlyTraceFlag party_state_trace(false, "party_state");
DebugOnlyTraceFlag pending_tags_trace(false, "pending_tags");
DebugOnlyTraceFlag http2_ph2_transport_trace(false, "http2_ph2_transport");
DebugOnlyTraceFlag polling_trace(false, "polling");
DebugOnlyTraceFlag polling_api_trace(false, "polling_api");
DebugOnlyTraceFlag promise_primitives_trace(false, "promise_primitives");
DebugOnlyTraceFlag resolver_refcount_trace(false, "resolver_refcount");
DebugOnlyTraceFlag security_connector_refcount_trace(false, "security_connector_refcount");
DebugOnlyTraceFlag slice_refcount_trace(false, "slice_refcount");
DebugOnlyTraceFlag stream_refcount_trace(false, "stream_refcount");
DebugOnlyTraceFlag subchannel_refcount_trace(false, "subchannel_refcount");
DebugOnlyTraceFlag work_serializer_trace(false, "work_serializer");
DebugOnlyTraceFlag ztrace_trace(false, "ztrace");
TraceFlag api_trace(false, "api");
TraceFlag apple_polling_trace(false, "apple_polling");
TraceFlag backend_metric_trace(false, "backend_metric");
TraceFlag backend_metric_filter_trace(false, "backend_metric_filter");
TraceFlag bdp_estimator_trace(false, "bdp_estimator");
TraceFlag call_trace(false, "call");
TraceFlag call_error_trace(false, "call_error");
TraceFlag cares_address_sorting_trace(false, "cares_address_sorting");
TraceFlag cares_resolver_trace(false, "cares_resolver");
TraceFlag cds_lb_trace(false, "cds_lb");
TraceFlag channel_trace(false, "channel");
TraceFlag channel_stack_trace(false, "channel_stack");
TraceFlag chaotic_good_trace(false, "chaotic_good");
TraceFlag chttp2_hpack_parser_trace(false, "chttp2_hpack_parser");
TraceFlag chttp2_new_stream_trace(false, "chttp2_new_stream");
TraceFlag client_channel_trace(false, "client_channel");
TraceFlag client_channel_call_trace(false, "client_channel_call");
TraceFlag client_channel_lb_call_trace(false, "client_channel_lb_call");
TraceFlag client_idle_filter_trace(false, "client_idle_filter");
TraceFlag compression_trace(false, "compression");
TraceFlag connectivity_state_trace(false, "connectivity_state");
TraceFlag dns_resolver_trace(false, "dns_resolver");
TraceFlag environment_autodetect_trace(false, "environment_autodetect");
TraceFlag event_engine_trace(false, "event_engine");
TraceFlag event_engine_client_channel_resolver_trace(false, "event_engine_client_channel_resolver");
TraceFlag event_engine_dns_trace(false, "event_engine_dns");
TraceFlag event_engine_endpoint_trace(false, "event_engine_endpoint");
TraceFlag event_engine_endpoint_data_trace(false, "event_engine_endpoint_data");
TraceFlag event_engine_poller_trace(false, "event_engine_poller");
TraceFlag fault_injection_filter_trace(false, "fault_injection_filter");
TraceFlag flowctl_trace(false, "flowctl");
TraceFlag fork_trace(false, "fork");
TraceFlag fuzzing_ee_timers_trace(false, "fuzzing_ee_timers");
TraceFlag fuzzing_ee_writes_trace(false, "fuzzing_ee_writes");
TraceFlag glb_trace(false, "glb");
TraceFlag grpc_authz_api_trace(false, "grpc_authz_api");
TraceFlag handshaker_trace(false, "handshaker");
TraceFlag health_check_client_trace(false, "health_check_client");
TraceFlag http_trace(false, "http");
TraceFlag http1_trace(false, "http1");
TraceFlag http2_ping_trace(false, "http2_ping");
TraceFlag http2_stream_state_trace(false, "http2_stream_state");
TraceFlag http_keepalive_trace(false, "http_keepalive");
TraceFlag inproc_trace(false, "inproc");
TraceFlag metadata_query_trace(false, "metadata_query");
TraceFlag op_failure_trace(false, "op_failure");
TraceFlag orca_client_trace(false, "orca_client");
TraceFlag outlier_detection_lb_trace(false, "outlier_detection_lb");
TraceFlag pick_first_trace(false, "pick_first");
TraceFlag plugin_credentials_trace(false, "plugin_credentials");
TraceFlag priority_lb_trace(false, "priority_lb");
TraceFlag queue_pluck_trace(false, "queue_pluck");
TraceFlag resource_quota_trace(false, "resource_quota");
TraceFlag retry_trace(false, "retry");
TraceFlag ring_hash_lb_trace(false, "ring_hash_lb");
TraceFlag rls_lb_trace(false, "rls_lb");
TraceFlag round_robin_trace(false, "round_robin");
TraceFlag secure_endpoint_trace(false, "secure_endpoint");
TraceFlag server_channel_trace(false, "server_channel");
TraceFlag stateful_session_filter_trace(false, "stateful_session_filter");
TraceFlag subchannel_trace(false, "subchannel");
TraceFlag subchannel_pool_trace(false, "subchannel_pool");
TraceFlag tcp_trace(false, "tcp");
TraceFlag timer_trace(false, "timer");
TraceFlag timer_check_trace(false, "timer_check");
TraceFlag token_fetcher_credentials_trace(false, "token_fetcher_credentials");
TraceFlag tsi_trace(false, "tsi");
TraceFlag weighted_round_robin_lb_trace(false, "weighted_round_robin_lb");
TraceFlag weighted_target_lb_trace(false, "weighted_target_lb");
TraceFlag xds_client_trace(false, "xds_client");
TraceFlag xds_client_refcount_trace(false, "xds_client_refcount");
TraceFlag xds_cluster_impl_lb_trace(false, "xds_cluster_impl_lb");
TraceFlag xds_cluster_manager_lb_trace(false, "xds_cluster_manager_lb");
TraceFlag xds_override_host_lb_trace(false, "xds_override_host_lb");
TraceFlag xds_resolver_trace(false, "xds_resolver");
TraceFlag xds_server_config_fetcher_trace(false, "xds_server_config_fetcher");
TraceFlag xds_wrr_locality_lb_trace(false, "xds_wrr_locality_lb");

const absl::flat_hash_map<std::string, TraceFlag*>& GetAllTraceFlags() {
  static const NoDestruct<absl::flat_hash_map<std::string, TraceFlag*>> all(
      absl::flat_hash_map<std::string, TraceFlag*>({
          {"api", &api_trace},
          {"apple_polling", &apple_polling_trace},
          {"backend_metric", &backend_metric_trace},
          {"backend_metric_filter", &backend_metric_filter_trace},
          {"bdp_estimator", &bdp_estimator_trace},
          {"call", &call_trace},
          {"call_error", &call_error_trace},
          {"cares_address_sorting", &cares_address_sorting_trace},
          {"cares_resolver", &cares_resolver_trace},
          {"cds_lb", &cds_lb_trace},
          {"channel", &channel_trace},
          {"channel_stack", &channel_stack_trace},
          {"chaotic_good", &chaotic_good_trace},
          {"chttp2_hpack_parser", &chttp2_hpack_parser_trace},
          {"chttp2_new_stream", &chttp2_new_stream_trace},
          {"client_channel", &client_channel_trace},
          {"client_channel_call", &client_channel_call_trace},
          {"client_channel_lb_call", &client_channel_lb_call_trace},
          {"client_idle_filter", &client_idle_filter_trace},
          {"compression", &compression_trace},
          {"connectivity_state", &connectivity_state_trace},
          {"dns_resolver", &dns_resolver_trace},
          {"environment_autodetect", &environment_autodetect_trace},
          {"event_engine", &event_engine_trace},
          {"event_engine_client_channel_resolver", &event_engine_client_channel_resolver_trace},
          {"event_engine_dns", &event_engine_dns_trace},
          {"event_engine_endpoint", &event_engine_endpoint_trace},
          {"event_engine_endpoint_data", &event_engine_endpoint_data_trace},
          {"event_engine_poller", &event_engine_poller_trace},
          {"fault_injection_filter", &fault_injection_filter_trace},
          {"flowctl", &flowctl_trace},
          {"fork", &fork_trace},
          {"fuzzing_ee_timers", &fuzzing_ee_timers_trace},
          {"fuzzing_ee_writes", &fuzzing_ee_writes_trace},
          {"glb", &glb_trace},
          {"grpc_authz_api", &grpc_authz_api_trace},
          {"handshaker", &handshaker_trace},
          {"health_check_client", &health_check_client_trace},
          {"http", &http_trace},
          {"http1", &http1_trace},
          {"http2_ping", &http2_ping_trace},
          {"http2_stream_state", &http2_stream_state_trace},
          {"http_keepalive", &http_keepalive_trace},
          {"inproc", &inproc_trace},
          {"metadata_query", &metadata_query_trace},
          {"op_failure", &op_failure_trace},
          {"orca_client", &orca_client_trace},
          {"outlier_detection_lb", &outlier_detection_lb_trace},
          {"pick_first", &pick_first_trace},
          {"plugin_credentials", &plugin_credentials_trace},
          {"priority_lb", &priority_lb_trace},
          {"queue_pluck", &queue_pluck_trace},
          {"resource_quota", &resource_quota_trace},
          {"retry", &retry_trace},
          {"ring_hash_lb", &ring_hash_lb_trace},
          {"rls_lb", &rls_lb_trace},
          {"round_robin", &round_robin_trace},
          {"secure_endpoint", &secure_endpoint_trace},
          {"server_channel", &server_channel_trace},
          {"stateful_session_filter", &stateful_session_filter_trace},
          {"subchannel", &subchannel_trace},
          {"subchannel_pool", &subchannel_pool_trace},
          {"tcp", &tcp_trace},
          {"timer", &timer_trace},
          {"timer_check", &timer_check_trace},
          {"token_fetcher_credentials", &token_fetcher_credentials_trace},
          {"tsi", &tsi_trace},
          {"weighted_round_robin_lb", &weighted_round_robin_lb_trace},
          {"weighted_target_lb", &weighted_target_lb_trace},
          {"xds_client", &xds_client_trace},
          {"xds_client_refcount", &xds_client_refcount_trace},
          {"xds_cluster_impl_lb", &xds_cluster_impl_lb_trace},
          {"xds_cluster_manager_lb", &xds_cluster_manager_lb_trace},
          {"xds_override_host_lb", &xds_override_host_lb_trace},
          {"xds_resolver", &xds_resolver_trace},
          {"xds_server_config_fetcher", &xds_server_config_fetcher_trace},
          {"xds_wrr_locality_lb", &xds_wrr_locality_lb_trace},
#ifndef NDEBUG
          {"auth_context_refcount", &auth_context_refcount_trace},
          {"call_combiner", &call_combiner_trace},
          {"call_refcount", &call_refcount_trace},
          {"call_state", &call_state_trace},
          {"chttp2_server_refcount", &chttp2_server_refcount_trace},
          {"closure", &closure_trace},
          {"combiner", &combiner_trace},
          {"cq_refcount", &cq_refcount_trace},
          {"error_refcount", &error_refcount_trace},
          {"fd_refcount", &fd_refcount_trace},
          {"fd_trace", &fd_trace_trace},
          {"lb_policy_refcount", &lb_policy_refcount_trace},
          {"party_state", &party_state_trace},
          {"pending_tags", &pending_tags_trace},
          {"http2_ph2_transport", &http2_ph2_transport_trace},
          {"polling", &polling_trace},
          {"polling_api", &polling_api_trace},
          {"promise_primitives", &promise_primitives_trace},
          {"resolver_refcount", &resolver_refcount_trace},
          {"security_connector_refcount", &security_connector_refcount_trace},
          {"slice_refcount", &slice_refcount_trace},
          {"stream_refcount", &stream_refcount_trace},
          {"subchannel_refcount", &subchannel_refcount_trace},
          {"work_serializer", &work_serializer_trace},
          {"ztrace", &ztrace_trace},
#endif
      }));
  return *all;
}

}  // namespace grpc_core
)";
  EXPECT_EQ(GenerateCpp({std::string(kInputYaml)}), expected_output);
}

TEST(GenerateTraceFlagsTest, GenerateMarkdown) {
  absl::string_view expected_output =
      R"(<!---
Automatically generated by tools/codegen/core/gen_trace_flags.py
--->

gRPC Trace Flags
----------------

The `GRPC_TRACE` environment variable supports a comma-separated list of tracer
names or glob patterns that provide additional insight into how gRPC C core is
processing requests via debug logs. Available tracers include:

  - api - API calls to the C core.
  - backend_metric - C++ backend metric recorder APIs.
  - backend_metric_filter - Filter that populates backend metric data in server trailing metadata.
  - bdp_estimator - Behavior of bdp estimation logic.
  - call - Traces operations on a call through the gRPC stack.
  - call_error - Possible errors contributing to final call statuses.
  - cares_address_sorting - Operations of the c-ares based DNS resolver's address sorter.
  - cares_resolver - Operations of the c-ares based DNS resolver.
  - cds_lb - CDS LB policy.
  - channel - Operations on the C core channel stack.
  - channel_stack - Construction of the set of filters in a channel stack.
  - chaotic_good - Chaotic good transport.
  - chttp2_hpack_parser - HTTP/2 HPACK parser.
  - chttp2_new_stream - HTTP/2 incoming stream creation.
  - client_channel - Client channel control plane activity, including resolver and load balancing policy interaction.
  - client_channel_call - Client channel call activity related to name resolution.
  - client_channel_lb_call - Client channel call activity related to load balancing picking.
  - client_idle_filter - Client idleness filter.
  - compression - Compression operations.
  - connectivity_state - Connectivity state changes to channels.
  - dns_resolver - The active DNS resolver.
  - environment_autodetect - GCP environment auto-detection.
  - event_engine - High-level EventEngine operations.
  - event_engine_client_channel_resolver - EventEngine-based client channel resolver state and events.
  - event_engine_dns - EventEngine DNS resolver.
  - event_engine_endpoint - EventEngine Endpoint operations.
  - event_engine_endpoint_data - Detailed dump of EventEngine endpoint TCP data.
  - event_engine_poller - EventEngine Poller events.
  - fault_injection_filter - Fault injection.
  - flowctl - Http2 flow control.
  - fork - Fork support.
  - glb - gRPClb load balancer.
  - grpc_authz_api - gRPC authorization.
  - handshaker - Handshaking state.
  - health_check_client - Health checking client code.
  - http - Http2 transport engine.
  - http1 - HTTP/1.x operations performed by gRPC.
  - http2_ping - Pings/ping acks/antagonist writes in http2 stack.
  - http2_stream_state - Http2 stream state mutations.
  - http_keepalive - gRPC keepalive pings.
  - inproc - In-process transport.
  - metadata_query - GCP metadata queries.
  - op_failure - Error information when failure is pushed onto a completion queue. The `api` tracer must be enabled for this flag to have any effect.
  - orca_client - Out-of-band backend metric reporting client.
  - outlier_detection_lb - Outlier detection.
  - pick_first - Pick first load balancing policy.
  - plugin_credentials - Plugin credentials.
  - priority_lb - Priority LB policy.
  - queue_pluck - Completion queue plucking. The `api` tracer must be enabled for this flag to have any effect.
  - resource_quota - Resource quota objects internals.
  - retry - Call retries.
  - ring_hash_lb - Ring hash load balancing policy.
  - rls_lb - RLS load balancing policy.
  - round_robin - Round robin load balancing policy.
  - secure_endpoint - Bytes flowing through encrypted channels.
  - server_channel - Lightweight trace of significant server channel events.
  - stateful_session_filter - Stateful session affinity.
  - subchannel - Connectivity state of subchannels.
  - subchannel_pool - Subchannel pool.
  - tcp - Bytes in and out of a channel.
  - timer - Timers (alarms) in the grpc internals.
  - timer_check - more detailed trace of timer logic in grpc internals.
  - token_fetcher_credentials - Token fetcher call credentials framework, used for (e.g.) oauth2 token fetcher credentials.
  - tsi - TSI transport security.
  - weighted_round_robin_lb - Weighted round robin load balancing policy.
  - weighted_target_lb - Weighted target LB policy.
  - xds_client - XDS client.
  - xds_client_refcount - Refcount of XDS client.
  - xds_cluster_impl_lb - XDS Cluster impl LB policy.
  - xds_cluster_manager_lb - XDS Cluster manager LB policy.
  - xds_override_host_lb - XDS Override host LB.
  - xds_resolver - XDS Resolver.
  - xds_server_config_fetcher - XDS Server config fetcher.
  - xds_wrr_locality_lb - XDS WRR locality LB policy.

The following tracers will only run in binaries built in DEBUG mode. This is
accomplished by invoking `bazel build --config=dbg <target>`
  - auth_context_refcount - Auth context refcounting.
  - call_combiner - Call combiner state.
  - call_refcount - Refcount on call.
  - call_state - Traces transitions through the call spine state machine.
  - chttp2_server_refcount - Refcounting in Chttp2 Server.
  - closure - Legacy closure creation, scheduling, and completion.
  - combiner - Combiner lock state.
  - cq_refcount - Completion queue refcounting.
  - error_refcount - Error refcounting.
  - fd_refcount - File descriptor refcounting.
  - fd_trace - Legacy file descriptor create(), shutdown() and close() calls for channel fds.
  - lb_policy_refcount - LB policy refcounting.
  - party_state - Coordination of activities related to a call.
  - pending_tags - Still-in-progress tags on completion queues. The `api` tracer must be enabled for this flag to have any effect.
  - http2_ph2_transport - Promise Based HTTP2 transport.
  - polling - The active polling engine.
  - polling_api - API calls to polling engine.
  - promise_primitives - Low-level primitives in the promise library.
  - resolver_refcount - Resolver refcouting.
  - security_connector_refcount - Refcounting for security connectors (part of channel credentials).
  - slice_refcount - Slice refcounting.
  - stream_refcount - Stream refcounting.
  - subchannel_refcount - Subchannel refcounting.
  - work_serializer - A synchronization mechanism used to ensure that only one thread is executing at a given time.
  - ztrace - Trace ztrace appends globally (for debugging the ztrace system itself).

Glob patterns and special cases:
  - `*` can be used to turn all traces on.
  - Individual traces can be disabled by prefixing them with `-`.
  - `*refcount*` will turn on all of the tracers for refcount debugging.
  - if `list_tracers` is present, then all of the available tracers will be
    printed when the program starts up.

Example:
export GRPC_TRACE=*,-pending_tags
)";
  EXPECT_EQ(GenerateMarkdown({std::string(kInputYaml)}), expected_output);
}

}  // namespace testing
}  // namespace grpc_generator
