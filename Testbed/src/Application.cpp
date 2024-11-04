#include "Application.hpp"

static const zth::ApplicationSpec spec = {
    .window_spec = {
        .title = "Testbed",
        .resolution = { 1920, 1080 },
        .fullscreen = false,
        .frame_rate_limit = 60,
    },
    .logger_spec = {
        .target = zth::LogTarget::ConsoleAndFile,
        .log_file_path = "../testbed_log.txt",
    },
};

Application::Application() : zth::Application(spec)
{
    zth::Logger::print_notification("On init.");
    _logger.log_error("Logger Test: {}, {}, {}.", 1, 2, 3);
    _window.set_clear_color(zth::Color::black);
}

Application::~Application()
{
    zth::Logger::print_notification("On shutdown.");
}

void Application::on_update([[maybe_unused]] const double delta_time)
{
    zth::Logger::print_notification("On Update with delta time: {} seconds.", delta_time);
    zth::Logger::print_notification("FPS: {}", get_fps());
    primitive_renderer_test();
}

void Application::on_event(const zth::Event& event, [[maybe_unused]] const double delta_time)
{
    event_test(event);
}
