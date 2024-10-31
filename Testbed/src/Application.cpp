#include "Application.hpp"

#include <Zenith/Timer.hpp>

#include "EventTest.hpp"
#include "PrimitiveRendererTest.hpp"

static const zth::ApplicationSpec spec = {
    .window_spec = {
        .title = "Sandbox",
        .resolution = { 1920, 1080 },
        .fullscreen = false,
        .frame_rate_limit = 60,
    },
    .logger_spec = {
        .target = zth::LogTarget::ConsoleAndFile,
        .log_file_path = "../log.txt",
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

static void count_fps()
{
    static zth::Timer fps_counter;
    static unsigned int frames = 0;
    frames++;

    if (fps_counter.elapsed_ms() > 1000)
    {
        zth::Logger::print_notification("FPS: {}", frames);
        frames = 0;
        fps_counter.reset();
    }
}

void Application::on_update([[maybe_unused]] const zth::u64 delta_time)
{
    // zth::Logger::print_notification("On Update with delta time: {} microseconds.", delta_time);
    count_fps();

    auto& renderer = _window.primitive_renderer;
    primitive_renderer_test(renderer);
}

void Application::on_event(const zth::Event& event)
{
    event_test(event);
}
