// Copyright Zhaoqing Qiang
// SPDX-License-Identifier: Apache-2.0

#include "opentelemetry/exporters/otlp/otlp_http_exporter_factory.h"
#include "opentelemetry/exporters/otlp/otlp_http_exporter_options.h"
#include "opentelemetry/sdk/common/global_log_handler.h"
#include "opentelemetry/sdk/trace/simple_processor_factory.h"
#include "opentelemetry/sdk/trace/tracer_provider_factory.h"
#include "opentelemetry/trace/provider.h"

// sdk::TracerProvider is just used to call ForceFlush and prevent to cancel running exportings when
// destroy and shutdown exporters.It's optional to users.
#include "opentelemetry/sdk/trace/tracer_provider.h"

#include <string>

namespace trace     = opentelemetry::trace;
namespace trace_sdk = opentelemetry::sdk::trace;
namespace otlp      = opentelemetry::exporter::otlp;

namespace internal_log = opentelemetry::sdk::common::internal_log;
namespace nostd        = opentelemetry::nostd;

opentelemetry::exporter::otlp::OtlpHttpExporterOptions opts;

nostd::shared_ptr<trace::Tracer> get_tracer()
{
  auto provider = trace::Provider::GetTracerProvider();
  return provider->GetTracer("c_sdk", OPENTELEMETRY_SDK_VERSION);
}

/*
  Usage:
  - bin
  - bin <URL>
  - bin <URL> <DEBUG>
  - bin <URL> <DEBUG> <BIN>
  <DEBUG> = yes|no, to turn console debug on or off
  <BIN> = bin, to export in binary format
*/

extern "C" void InitOptions(char *url)
{
  opts.url           = url;
  std::string debug  = "yes";
  opts.console_debug = debug != "" && debug != "0" && debug != "no";
  if (opts.console_debug)
  {
    internal_log::GlobalLogHandler::SetLogLevel(internal_log::LogLevel::Debug);
  }
}

extern "C" void InitTracer()
{
  // Create OTLP exporter instance
  auto exporter  = otlp::OtlpHttpExporterFactory::Create(opts);
  auto processor = trace_sdk::SimpleSpanProcessorFactory::Create(std::move(exporter));
  std::shared_ptr<opentelemetry::trace::TracerProvider> provider =
      trace_sdk::TracerProviderFactory::Create(std::move(processor));
  // Set the global trace provider
  trace::Provider::SetTracerProvider(provider);
}

extern "C" void CleanupTracer()
{
  // We call ForceFlush to prevent to cancel running exportings, It's optional.
  opentelemetry::nostd::shared_ptr<opentelemetry::trace::TracerProvider> provider =
      trace::Provider::GetTracerProvider();
  if (provider)
  {
    static_cast<trace_sdk::TracerProvider *>(provider.get())->ForceFlush();
  }

  std::shared_ptr<opentelemetry::trace::TracerProvider> none;
  trace::Provider::SetTracerProvider(none);
}

extern "C" void OnHttpRequest(const char *uri)
{
  auto scoped_span = trace::Scope(get_tracer()->StartSpan("OnHttpRequest"));
}