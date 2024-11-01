#include "Application.hpp"

static const zth::ApplicationSpec spec = {
    .window_spec = {
        .title = "Sandbox",
        .resolution = { 1920, 1080 },
        .fullscreen = false,
        .frame_rate_limit = 60,
    },
    .logger_spec = {
        .target = zth::LogTarget::ConsoleAndFile,
        .log_file_path = "../sandbox_log.txt",
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

void Application::on_update([[maybe_unused]] const zth::u64 delta_time)
{
    zth::Logger::print_notification("On Update with delta time: {} microseconds.", delta_time);
    zth::Logger::print_notification("FPS: {}", get_fps());
}

void Application::on_event(const zth::Event& event)
{
    switch (event.type())
    {
    case zth::EventType::WindowResized:
    {
        auto& resize_event = event.resize_event();
        zth::Logger::print_notification("Window resized. New size: ({}, {}).", resize_event.width, resize_event.height);
    }
    break;
    case zth::EventType::KeyPressed:
    {
        auto& key_event = event.key_event();
        zth::Logger::print_notification("{} key pressed.", to_string(key_event.key));
    }
    break;
    case zth::EventType::KeyReleased:
    {
        auto& key_event = event.key_event();
        zth::Logger::print_notification("{} key released.", to_string(key_event.key));
    }
    break;
    case zth::EventType::MouseButtonPressed:
    {
        auto& mouse_button_event = event.mouse_button_event();
        auto [pos_x, pos_y] = mouse_button_event.cursor_pos;
        zth::Logger::print_notification("{} mouse button pressed. Cursor pos: ({}, {}).",
                                        to_string(mouse_button_event.button), pos_x, pos_y);
    }
    break;
    case zth::EventType::MouseButtonReleased:
    {
        auto& mouse_button_event = event.mouse_button_event();
        auto [pos_x, pos_y] = mouse_button_event.cursor_pos;
        zth::Logger::print_notification("{} mouse button released. Cursor pos: ({}, {}).",
                                        to_string(mouse_button_event.button), pos_x, pos_y);
    }
    break;
    default:
        break;
    }
}
