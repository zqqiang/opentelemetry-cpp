# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

add_library(opentelemetry_c_sdk c_sdk.h c_sdk.cc)

include_directories(
  ${CMAKE_BINARY_DIR}/generated/third_party/opentelemetry-proto
  ${CMAKE_SOURCE_DIR}/exporters/otlp/include)

target_link_libraries(opentelemetry_c_sdk PUBLIC ${CMAKE_THREAD_LIBS_INIT}
                                                opentelemetry_api)

