# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

add_subdirectory(common)
include_directories(common)
if(WITH_OTLP_GRPC OR WITH_OTLP_HTTP)
  add_subdirectory(otlp)
endif()
if(WITH_OTLP_GRPC)
  add_subdirectory(grpc)
endif()
if(WITH_ETW)
  add_subdirectory(etw_threads)
endif()
if(WITH_JAEGER)
  add_subdirectory(jaeger)
endif()
if(WITH_ZIPKIN)
  add_subdirectory(zipkin)
endif()
if(WITH_PROMETHEUS)
  add_subdirectory(prometheus)
endif()
if(WITH_LOGS_PREVIEW)
  add_subdirectory(logs_simple)
endif()
add_subdirectory(plugin)
add_subdirectory(simple)
add_subdirectory(batch)
add_subdirectory(metrics_simple)
add_subdirectory(multithreaded)
add_subdirectory(multi_processor)

if(WITH_EXAMPLES_HTTP)
  add_subdirectory(http)
endif()
