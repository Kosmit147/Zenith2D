#pragma once

#include <SFML/Window/Event.hpp>

#include <array>
#include <cassert>
#include <optional>

#include "Zenith/Platform/Input.hpp"
#include "Zenith/Platform/Resolution.hpp"

namespace zth {

struct KeyEvent
{
    Key key;
};

struct ResizeEvent
{
    Resolution new_res;
};

struct MouseScrollEvent
{
    float delta; // wheel offset (positive is up, negative is down)
    CursorPos cursor_pos;
};

struct MouseButtonEvent
{
    MouseButton button;
    CursorPos cursor_pos;
};

struct MouseMoveEvent
{
    CursorPos new_cursor_pos;
};

enum class EventType
{
    // keep this list consistent with the array below

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

inline constexpr std::array event_type_enumerations = {
    // clang-format off
    EventType::WindowClosed,
    EventType::WindowResized,
    EventType::LostFocus,
    EventType::GainedFocus,
    EventType::KeyPressed,
    EventType::KeyReleased,
    EventType::MouseWheelScrolled,
    EventType::MouseButtonPressed,
    EventType::MouseButtonReleased,
    EventType::MouseMoved,
    EventType::MouseEntered,
    EventType::MouseLeft,
    // clang-format on
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
    static std::optional<Event> from_sf_event(const sf::Event& event);
    explicit Event(EventType event_type);
    explicit Event(EventType event_type, const ResizeEvent& resize_event);
    explicit Event(EventType event_type, const KeyEvent& key_event);
    explicit Event(EventType event_type, const MouseScrollEvent& mouse_scroll_event);
    explicit Event(EventType event_type, const MouseButtonEvent& mouse_button_event);
    explicit Event(EventType event_type, const MouseMoveEvent& mouse_move_event);

    friend class Window;

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
};

} // namespace zth
