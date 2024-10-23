#include "Event.hpp"

namespace zth {

std::optional<Event> Event::create_from_sf_event(const sf::Event& event)
{
    std::optional<Event> ret = {};

    switch (event.type)
    {
    case sf::Event::Closed:
    {
        ret = { EventType::WindowClosed };
    }
    break;
    case sf::Event::Resized:
    {
        ret = { EventType::WindowResized, ResizeEvent{ event.size.width, event.size.height } };
    }
    break;
    case sf::Event::LostFocus:
    {
        ret = { EventType::LostFocus };
    }
    break;
    case sf::Event::GainedFocus:
    {
        ret = { EventType::GainedFocus };
    }
    break;
    case sf::Event::KeyPressed:
    {
        ret = { EventType::KeyPressed, KeyEvent{ .key = key_from_sf_scancode(event.key.scancode) } };
    }
    break;
    case sf::Event::KeyReleased:
    {
        ret = { EventType::KeyReleased, KeyEvent{ .key = key_from_sf_scancode(event.key.scancode) } };
    }
    break;
    case sf::Event::MouseWheelScrolled:
    {
        CursorPos cursor_pos{ event.mouseWheelScroll.x, event.mouseWheelScroll.y };
        MouseScrollEvent mouse_scroll_event = MouseScrollEvent{ event.mouseWheelScroll.delta, cursor_pos };

        ret = { EventType::MouseWheelScrolled, mouse_scroll_event };
    }
    break;
    case sf::Event::MouseButtonPressed:
    {
        MouseButton button = event.mouseButton.button == sf::Mouse::Left ? MouseButton::Left : MouseButton::Right;
        CursorPos cursor_pos{ event.mouseButton.x, event.mouseButton.y };

        ret = { EventType::MouseButtonPressed, MouseButtonEvent{ button, cursor_pos } };
    }
    break;
    case sf::Event::MouseButtonReleased:
    {
        MouseButton button = event.mouseButton.button == sf::Mouse::Left ? MouseButton::Left : MouseButton::Right;
        CursorPos cursor_pos{ event.mouseButton.x, event.mouseButton.y };

        ret = { EventType::MouseButtonReleased, MouseButtonEvent{ button, cursor_pos } };
    }
    break;
    case sf::Event::MouseMoved:
    {
        CursorPos cursor_pos{ event.mouseMove.x, event.mouseMove.y };

        ret = { EventType::MouseMoved, MouseMoveEvent{ cursor_pos } };
    }
    break;
    case sf::Event::MouseEntered:
    {
        ret = { EventType::MouseEntered };
    }
    break;
    case sf::Event::MouseLeft:
    {
        ret = { EventType::MouseLeft };
    }
    break;
    default:
    {
        // TODO: handle all switch cases
    }
    break;
    }

    return ret;
}

} // namespace zth
