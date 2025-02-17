# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

add_library(
  opentelemetry_metrics
  async_instruments.cc
  meter_provider.cc
  meter.cc
  meter_context.cc
  metric_reader.cc
  instrument_metadata_validator.cc
  export/periodic_exporting_metric_reader.cc
  state/metric_collector.cc
  state/observable_registry.cc
  state/sync_metric_storage.cc
  state/temporal_metric_storage.cc
  aggregation/histogram_aggregation.cc
  aggregation/lastvalue_aggregation.cc
  aggregation/sum_aggregation.cc
  exemplar/filter.cc
  exemplar/reservoir.cc
  sync_instruments.cc)

set_target_properties(opentelemetry_metrics PROPERTIES EXPORT_NAME metrics)

target_link_libraries(opentelemetry_metrics PUBLIC opentelemetry_common)

target_include_directories(
  opentelemetry_metrics
  PUBLIC "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/sdk/include>")

if(OPENTELEMETRY_INSTALL)
  install(
    TARGETS opentelemetry_metrics
    EXPORT "${PROJECT_NAME}-target"
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
endif()
