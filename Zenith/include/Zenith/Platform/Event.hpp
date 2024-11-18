#pragma once

#include <SFML/Window/Event.hpp>

#include <array>
#include <cassert>
#include <optional>

#include "Zenith/Platform/Input/Input.hpp"
#include "Zenith/Platform/Resolution.hpp"

namespace zth {

/**
 * @brief Represents a keyboard event.
 */
struct KeyEvent
{
    Key key; ///< The key involved in the event.
};

/**
 * @brief Represents a window resize event.
 */
struct ResizeEvent
{
    Resolution new_res; ///< The new resolution after the resize.
};

/**
 * @brief Represents a mouse scroll event.
 */
struct MouseScrollEvent
{
    float delta; ///< The wheel offset (positive is up, negative is down).
    CursorPos cursor_pos; ///< The cursor position at the time of scrolling.
};

/**
 * @brief Represents a mouse button event (press or release).
 */
struct MouseButtonEvent
{
    MouseButton button; ///< The button involved in the event.
    CursorPos cursor_pos; ///< The cursor position at the time of the event.
};

/**
 * @brief Represents a mouse movement event.
 */
struct MouseMoveEvent
{
    CursorPos new_cursor_pos; ///< The new cursor position after movement.
};

/**
 * @brief Enum class representing different types of events.
 */
enum class EventType
{
    WindowClosed,        ///< The window was closed.
    WindowResized,       ///< The window was resized.
    LostFocus,           ///< The window lost focus.
    GainedFocus,         ///< The window gained focus.
    KeyPressed,          ///< A key was pressed.
    KeyReleased,         ///< A key was released.
    MouseWheelScrolled,  ///< The mouse wheel was scrolled.
    MouseButtonPressed,  ///< A mouse button was pressed.
    MouseButtonReleased, ///< A mouse button was released.
    MouseMoved,          ///< The mouse was moved.
    MouseEntered,        ///< The mouse entered the window.
    MouseLeft,           ///< The mouse left the window.
};

/**
 * @brief A constexpr array that holds all possible event types.
 */
inline constexpr std::array event_type_enumerations = {
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
};

/**
 * @brief Represents an event (e.g., key press, mouse click, window resize).
 * 
 * The `Event` class is used to store various types of events that occur during the application's runtime. 
 * Each event contains specific data depending on the event type.
 */
class Event
{
public:
    /**
     * @brief Gets the event type.
     * 
     * @return The type of the event.
     */
    auto type() const { return _type; }

    /**
     * @brief Gets the associated key event (only valid for `KeyPressed` and `KeyReleased` events).
     * 
     * @return A reference to the `KeyEvent` associated with the event.
     * @throws std::assertion_failure If the event type is not `KeyPressed` or `KeyReleased`.
     */
    auto& key_event() const
    {
        assert(_type == EventType::KeyPressed || _type == EventType::KeyReleased);
        return _key_event;
    }

    /**
     * @brief Gets the associated resize event (only valid for `WindowResized` events).
     * 
     * @return A reference to the `ResizeEvent` associated with the event.
     * @throws std::assertion_failure If the event type is not `WindowResized`.
     */
    auto& resize_event() const
    {
        assert(_type == EventType::WindowResized);
        return _resize_event;
    }

    /**
     * @brief Gets the associated mouse scroll event (only valid for `MouseWheelScrolled` events).
     * 
     * @return A reference to the `MouseScrollEvent` associated with the event.
     * @throws std::assertion_failure If the event type is not `MouseWheelScrolled`.
     */
    auto& mouse_scroll_event() const
    {
        assert(_type == EventType::MouseWheelScrolled);
        return _mouse_scroll_event;
    }

    /**
     * @brief Gets the associated mouse button event (only valid for `MouseButtonPressed` or `MouseButtonReleased` events).
     * 
     * @return A reference to the `MouseButtonEvent` associated with the event.
     * @throws std::assertion_failure If the event type is not `MouseButtonPressed` or `MouseButtonReleased`.
     */
    auto& mouse_button_event() const
    {
        assert(_type == EventType::MouseButtonPressed || _type == EventType::MouseButtonReleased);
        return _mouse_button_event;
    }

    /**
     * @brief Gets the associated mouse move event (only valid for `MouseMoved` events).
     * 
     * @return A reference to the `MouseMoveEvent` associated with the event.
     * @throws std::assertion_failure If the event type is not `MouseMoved`.
     */
    auto& mouse_move_event() const
    {
        assert(_type == EventType::MouseMoved);
        return _mouse_move_event;
    }

    /**
     * @brief Determines whether the event is related to user input (mouse or keyboard).
     * 
     * @return `true` if the event is related to user input (key press, mouse click, etc.), `false` otherwise.
     */
    bool is_input_event() const;

private:
    /**
     * @brief Converts an `sf::Event` to a Zenith `Event`.
     * 
     * @param event The `sf::Event` to convert.
     * @return An `optional<Event>` containing the converted event, or `nullopt` if the conversion fails.
     */
    static std::optional<Event> from_sf_event(const sf::Event& event);

    /**
     * @brief Constructs an `Event` with a specified type.
     * 
     * @param event_type The type of event.
     */
    explicit Event(EventType event_type);

    /**
     * @brief Constructs an `Event` with a `ResizeEvent` for a window resize.
     * 
     * @param event_type The type of event (must be `WindowResized`).
     * @param resize_event The resize event data.
     */
    explicit Event(EventType event_type, const ResizeEvent& resize_event);

    /**
     * @brief Constructs an `Event` with a `KeyEvent` for a key press or release.
     * 
     * @param event_type The type of event (must be `KeyPressed` or `KeyReleased`).
     * @param key_event The key event data.
     */
    explicit Event(EventType event_type, const KeyEvent& key_event);

    /**
     * @brief Constructs an `Event` with a `MouseScrollEvent` for mouse wheel scrolling.
     * 
     * @param event_type The type of event (must be `MouseWheelScrolled`).
     * @param mouse_scroll_event The mouse scroll event data.
     */
    explicit Event(EventType event_type, const MouseScrollEvent& mouse_scroll_event);

    /**
     * @brief Constructs an `Event` with a `MouseButtonEvent` for mouse button press or release.
     * 
     * @param event_type The type of event (must be `MouseButtonPressed` or `MouseButtonReleased`).
     * @param mouse_button_event The mouse button event data.
     */
    explicit Event(EventType event_type, const MouseButtonEvent& mouse_button_event);

    /**
     * @brief Constructs an `Event` with a `MouseMoveEvent` for mouse movement.
     * 
     * @param event_type The type of event (must be `MouseMoved`).
     * @param mouse_move_event The mouse move event data.
     */
    explicit Event(EventType event_type, const MouseMoveEvent& mouse_move_event);

    friend class Window;

private:
    EventType _type; ///< The type of the event.

    /**
     * @brief Union storing the event data. 
     * Each event type will use a specific part of this union.
     */
    union
    {
        bool _dummy; ///< A dummy field used when no event data is needed.
        ResizeEvent _resize_event; ///< The resize event data.
        KeyEvent _key_event; ///< The key event data.
        MouseScrollEvent _mouse_scroll_event; ///< The mouse scroll event data.
        MouseButtonEvent _mouse_button_event; ///< The mouse button event data.
        MouseMoveEvent _mouse_move_event; ///< The mouse move event data.
    };
};

} // namespace zth
