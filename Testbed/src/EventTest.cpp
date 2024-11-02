#include "EventTest.hpp"

#include <Zenith/Logging/Logger.hpp>

void event_test(const zth::Event& event)
{
    switch (event.type())
    {
    case zth::EventType::WindowResized:
    {
        auto& resize_event = event.resize_event();
        zth::Logger::print_notification("Window resized. New size: ({}, {}).", resize_event.width, resize_event.height);
    }
    break;
    case zth::EventType::LostFocus:
    {
        zth::Logger::print_notification("Lost focus.");
    }
    break;
    case zth::EventType::GainedFocus:
    {
        zth::Logger::print_notification("Gained focus.");
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
    case zth::EventType::MouseWheelScrolled:
    {
        auto& scroll_event = event.mouse_scroll_event();
        auto [pos_x, pos_y] = scroll_event.cursor_pos;
        zth::Logger::print_notification("Mouse scrolled: {}. Cursor pos: ({}, {}).", scroll_event.delta, pos_x, pos_y);
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
    case zth::EventType::MouseMoved:
    {
        auto& mouse_move_event = event.mouse_move_event();
        auto [pos_x, pos_y] = mouse_move_event.cursor_pos;
        zth::Logger::print_notification("Mouse moved. New cursor pos: ({}, {}).", pos_x, pos_y);
    }
    break;
    case zth::EventType::MouseEntered:
    {
        zth::Logger::print_notification("Mouse entered.");
    }
    break;
    case zth::EventType::MouseLeft:
    {
        zth::Logger::print_notification("Mouse left.");
    }
    break;
    default:
        break;
    }
}
