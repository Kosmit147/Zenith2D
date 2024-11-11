#include "Testbed.hpp"

#include <Zenith/Core/Engine.hpp>
#include <Zenith/Logging/Logger.hpp>

static const zth::ApplicationSpec spec = {
    .window_spec = {
        .title = "Testbed",
        .resolution = { 1920, 1080 },
        .fullscreen = false,
        .frame_rate_limit = 60,
    },
    .logger_spec = {
        .target = zth::LogTarget::ConsoleAndFile,
        .log_file_path = "log/testbed_log.txt",
    },
};

ZTH_IMPLEMENT_APP(Testbed)

Testbed::Testbed() : Application(spec)
{
    zth::logger->log_notification("On init.");
    zth::logger->log_error("Logger Test: {}, {}, {}.", 1, 2, 3);
    zth::engine->window.clear_color = zth::Color::black;
}

Testbed::~Testbed()
{
    zth::logger->log_notification("On shutdown.");
}

void Testbed::on_update()
{
    zth::Logger::print_notification("On Update with delta time: {} seconds.", zth::engine->delta_time());
    zth::Logger::print_notification("FPS: {}", zth::engine->fps());
    primitive_renderer_test();
}

void Testbed::on_event(const zth::Event& event)
{
    event_test(event);
}
