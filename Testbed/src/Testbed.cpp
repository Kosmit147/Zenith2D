#include "Testbed.hpp"

#include "PrimitiveRendererTest.hpp"

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

Testbed::Testbed() : Application(spec)
{
    zth::logger->log_notification("On init.");
    zth::logger->log_error("Logger Test: {}, {}, {}.", 1, 2, 3);
    zth::engine->window.clear_color = zth::Color::black;
    zth::engine->change_scene(std::make_unique<PrimitiveRendererTest>(zth::engine->window.renderer));
}

Testbed::~Testbed()
{
    zth::logger->log_notification("On shutdown.");
}

void Testbed::on_update()
{
    zth::Logger::print_notification("On Update with delta time: {} seconds.", zth::engine->delta_time());
    zth::Logger::print_notification("FPS: {}", zth::engine->fps());
}

void Testbed::on_event(const zth::Event& event)
{
    event_test(event);

    // switch (event.type())
    // {
    // case zth::EventType::KeyPressed:
    // {
    //     auto& key_event = event.key_event();
    //     switch (key_event.key)
    //     {
    //     case zth::Key::A:
    //         change_scene_back();
    //         break;
    //     case zth::Key::D:
    //         change_scene_forward();
    //         break;
    //     }
    // }
    // }
}

// void Testbed::change_scene_back()
// {
// }
// 
// void Testbed::change_scene_forward()
// {
// }

void Testbed::event_test(const zth::Event& event)
{
    switch (event.type())
    {
        using enum zth::EventType;
    case WindowResized:
    {
        auto& resize_event = event.resize_event();
        auto& new_res = resize_event.new_res;
        zth::Logger::print_notification("Window resized. New size: ({}, {}).", new_res.width, new_res.height);
    }
    break;
    case LostFocus:
    {
        zth::Logger::print_notification("Lost focus.");
    }
    break;
    case GainedFocus:
    {
        zth::Logger::print_notification("Gained focus.");
    }
    break;
    case KeyPressed:
    {
        auto& key_event = event.key_event();
        zth::Logger::print_notification("{} key pressed.", to_string(key_event.key));
    }
    break;
    case KeyReleased:
    {
        auto& key_event = event.key_event();
        zth::Logger::print_notification("{} key released.", to_string(key_event.key));
    }
    break;
    case MouseWheelScrolled:
    {
        auto& scroll_event = event.mouse_scroll_event();
        auto [pos_x, pos_y] = scroll_event.cursor_pos;
        zth::Logger::print_notification("Mouse scrolled: {}. Cursor pos: ({}, {}).", scroll_event.delta, pos_x, pos_y);
    }
    break;
    case MouseButtonPressed:
    {
        auto& mouse_button_event = event.mouse_button_event();
        auto [pos_x, pos_y] = mouse_button_event.cursor_pos;
        zth::Logger::print_notification("{} mouse button pressed. Cursor pos: ({}, {}).",
                                        to_string(mouse_button_event.button), pos_x, pos_y);
    }
    break;
    case MouseButtonReleased:
    {
        auto& mouse_button_event = event.mouse_button_event();
        auto [pos_x, pos_y] = mouse_button_event.cursor_pos;
        zth::Logger::print_notification("{} mouse button released. Cursor pos: ({}, {}).",
                                        to_string(mouse_button_event.button), pos_x, pos_y);
    }
    break;
    case MouseMoved:
    {
        auto& mouse_move_event = event.mouse_move_event();
        auto [pos_x, pos_y] = mouse_move_event.new_cursor_pos;
        zth::Logger::print_notification("Mouse moved. New cursor pos: ({}, {}).", pos_x, pos_y);
    }
    break;
    case MouseEntered:
    {
        zth::Logger::print_notification("Mouse entered.");
    }
    break;
    case MouseLeft:
    {
        zth::Logger::print_notification("Mouse left.");
    }
    break;
    default:
        break;
    }
}
