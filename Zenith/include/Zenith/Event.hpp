#pragma once

#include <SFML/Window/Event.hpp>

#include <cassert>
#include <optional>

#include "Input.hpp"
#include "Typedefs.hpp"

namespace zth {

struct KeyEvent
{
    Key key;
};

struct ResizeEvent
{
    u32 width;
    u32 height;
};

struct MouseScrollEvent
{
    float delta; // wheel offset (positive is up/left, negative is down/right)
    CursorPos cursor_pos;
};

struct MouseButtonEvent
{
    MouseButton button;
    CursorPos cursor_pos;
};

struct MouseMoveEvent
{
    CursorPos cursor_pos;
};

enum class EventType
{
    WindowClosed,
    WindowResized,
    LostFocus,
    GainedFocus,
    KeyPressed,
    KeyReleased,
    MouseWheelScrolled,
    MouseButtonPressed,
    MouseButtonReleased,
    MouseMoved,
    MouseEntered,
    MouseLeft,
};

class Event
{
public:
    auto type() const { return _type; }

    auto& key_event() const
    {
        assert(_type == EventType::KeyPressed || _type == EventType::KeyReleased);
        return _key_event;
    }

    auto& resize_event() const
    {
        assert(_type == EventType::WindowResized);
        return _resize_event;
    }

    auto& mouse_scroll_event() const
    {
        assert(_type == EventType::MouseWheelScrolled);
        return _mouse_scroll_event;
    }

    auto& mouse_button_event() const
    {
        assert(_type == EventType::MouseButtonPressed || _type == EventType::MouseButtonReleased);
        return _mouse_button_event;
    }

    auto& mouse_move_event() const
    {
        assert(_type == EventType::MouseMoved);
        return _mouse_move_event;
    }

private:
    static std::optional<Event> create_from_sf_event(const sf::Event& event);
    explicit Event(EventType event_type) : _type(event_type), _dummy(false) {}
    explicit Event(EventType event_type, ResizeEvent resize_event) : _type(event_type), _resize_event(resize_event) {}
    explicit Event(EventType event_type, KeyEvent key_event) : _type(event_type), _key_event(key_event) {}
    explicit Event(EventType event_type, MouseScrollEvent mouse_scroll_event)
        : _type(event_type), _mouse_scroll_event(mouse_scroll_event)
    {}
    explicit Event(EventType event_type, MouseButtonEvent mouse_button_event)
        : _type(event_type), _mouse_button_event(mouse_button_event)
    {}
    explicit Event(EventType event_type, MouseMoveEvent mouse_move_event)
        : _type(event_type), _mouse_move_event(mouse_move_event)
    {}

private:
    EventType _type;

    union
    {
        bool _dummy;
        ResizeEvent _resize_event;
        KeyEvent _key_event;
        MouseScrollEvent _mouse_scroll_event;
        MouseButtonEvent _mouse_button_event;
        MouseMoveEvent _mouse_move_event;
    };

    friend class Window;
};

} // namespace zth
