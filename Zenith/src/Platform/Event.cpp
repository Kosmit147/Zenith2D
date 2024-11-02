#include "Zenith/Platform/Event.hpp"

namespace zth {

std::optional<Event> Event::create_from_sf_event(const sf::Event& event)
{
    std::optional<Event> ret = {};

    switch (event.type)
    {
    case sf::Event::Closed:
    {
        ret = Event{ EventType::WindowClosed };
    }
    break;
    case sf::Event::Resized:
    {
        ret = Event{ EventType::WindowResized, ResizeEvent{ event.size.width, event.size.height } };
    }
    break;
    case sf::Event::LostFocus:
    {
        ret = Event{ EventType::LostFocus };
    }
    break;
    case sf::Event::GainedFocus:
    {
        ret = Event{ EventType::GainedFocus };
    }
    break;
    case sf::Event::KeyPressed:
    {
        ret = Event{ EventType::KeyPressed, KeyEvent{ .key = key_from_sf_scancode(event.key.scancode) } };
    }
    break;
    case sf::Event::KeyReleased:
    {
        ret = Event{ EventType::KeyReleased, KeyEvent{ .key = key_from_sf_scancode(event.key.scancode) } };
    }
    break;
    case sf::Event::MouseWheelScrolled:
    {
        CursorPos cursor_pos{ event.mouseWheelScroll.x, event.mouseWheelScroll.y };
        auto mouse_scroll_event = MouseScrollEvent{ event.mouseWheelScroll.delta, cursor_pos };

        ret = Event{ EventType::MouseWheelScrolled, mouse_scroll_event };
    }
    break;
    case sf::Event::MouseButtonPressed:
    {
        MouseButton button = event.mouseButton.button == sf::Mouse::Left ? MouseButton::Left : MouseButton::Right;
        CursorPos cursor_pos{ event.mouseButton.x, event.mouseButton.y };

        ret = Event{ EventType::MouseButtonPressed, MouseButtonEvent{ button, cursor_pos } };
    }
    break;
    case sf::Event::MouseButtonReleased:
    {
        MouseButton button = event.mouseButton.button == sf::Mouse::Left ? MouseButton::Left : MouseButton::Right;
        CursorPos cursor_pos{ event.mouseButton.x, event.mouseButton.y };

        ret = Event{ EventType::MouseButtonReleased, MouseButtonEvent{ button, cursor_pos } };
    }
    break;
    case sf::Event::MouseMoved:
    {
        CursorPos cursor_pos{ event.mouseMove.x, event.mouseMove.y };

        ret = Event{ EventType::MouseMoved, MouseMoveEvent{ cursor_pos } };
    }
    break;
    case sf::Event::MouseEntered:
    {
        ret = Event{ EventType::MouseEntered };
    }
    break;
    case sf::Event::MouseLeft:
    {
        ret = Event{ EventType::MouseLeft };
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
