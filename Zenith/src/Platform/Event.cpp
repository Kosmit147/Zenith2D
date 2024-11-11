#include "Zenith/Platform/Event.hpp"

namespace zth {

bool Event::is_input_event() const
{
    static constexpr std::array input_events = {
        EventType::KeyPressed,          EventType::KeyReleased, EventType::MouseButtonPressed,
        EventType::MouseButtonReleased, EventType::MouseMoved,
    };

    if (std::ranges::find(input_events, _type) != input_events.end())
        return true;
    else
        return false;
}

std::optional<Event> Event::from_sf_event(const sf::Event& event)
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
        ret = Event{ EventType::KeyPressed, KeyEvent{ .key = to_key(event.key.scancode) } };
    }
    break;
    case sf::Event::KeyReleased:
    {
        ret = Event{ EventType::KeyReleased, KeyEvent{ .key = to_key(event.key.scancode) } };
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
        auto button = to_mouse_button(event.mouseButton.button);
        CursorPos cursor_pos{ event.mouseButton.x, event.mouseButton.y };

        ret = Event{ EventType::MouseButtonPressed, MouseButtonEvent{ button, cursor_pos } };
    }
    break;
    case sf::Event::MouseButtonReleased:
    {
        auto button = to_mouse_button(event.mouseButton.button);
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

Event::Event(EventType event_type) : _type(event_type), _dummy(false) {}

Event::Event(EventType event_type, const ResizeEvent& resize_event) : _type(event_type), _resize_event(resize_event) {}

Event::Event(EventType event_type, const KeyEvent& key_event) : _type(event_type), _key_event(key_event) {}

Event::Event(EventType event_type, const MouseScrollEvent& mouse_scroll_event)
    : _type(event_type), _mouse_scroll_event(mouse_scroll_event)
{}

Event::Event(EventType event_type, const MouseButtonEvent& mouse_button_event)
    : _type(event_type), _mouse_button_event(mouse_button_event)
{}

Event::Event(EventType event_type, const MouseMoveEvent& mouse_move_event)
    : _type(event_type), _mouse_move_event(mouse_move_event)
{}

} // namespace zth
