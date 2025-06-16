#include "EntryPoint.h"
#include"framework/application.h"
#include<quill/Backend.h>
#include<quill/Frontend.h>
#include<quill/LogMacros.h>
#include<quill/Logger.h>
#include<quill/sinks/ConsoleSink.h>
#include <quill/std/Array.h>

int main() {

	quill::BackendOptions options;
	options.enable_yield_when_idle = true;
	options.transit_event_buffer_initial_capacity = 64;  // Reduce initial buffer size
	options.transit_events_soft_limit = 2048;  // Lower soft limit
	options.transit_events_hard_limit = 8192;  // Reduce max buffer size

	quill::Backend::start(options);
	auto console_sink = quill::Frontend::create_or_get_sink<quill::ConsoleSink>("sink_id_1");
	quill::Logger* logger = quill::Frontend::create_or_get_logger("root", std::move(console_sink));
	logger->set_log_level(quill::LogLevel::TraceL3);

	LOG_INFO(logger, "Start Logging in Entry");
	
	ly::Application* objApp = GetApplication();
	objApp->Run();

}