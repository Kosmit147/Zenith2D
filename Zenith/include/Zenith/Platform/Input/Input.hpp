#pragma once

#include "Keyboard.hpp"
#include "Mouse.hpp"
#include "Zenith/Core/Typedefs.hpp"

namespace zth {

/**
 * @brief A class responsible for managing and querying input state.
 * 
 * The `Input` class provides methods for checking the current state of the cursor position,
 * mouse buttons, and keyboard keys. It is typically used to check user input during the runtime
 * of an application, such as for responding to mouse movements or keyboard presses.
 */
class Input
{
public:
    /**
     * @brief Gets the current position of the cursor.
     * 
     * @return The current cursor position as a `CursorPos` object.
     */
    CursorPos cursor_pos() const;

    /**
     * @brief Checks if a specific mouse button is pressed.
     * 
     * @param button The mouse button to check.
     * @return `true` if the specified mouse button is pressed, `false` otherwise.
     */
    bool is_mouse_button_pressed(MouseButton button) const;

    /**
     * @brief Checks if a specific key is pressed.
     * 
     * @param key The key to check.
     * @return `true` if the specified key is pressed, `false` otherwise.
     */
    bool is_key_pressed(Key key) const;

    /**
     * @brief Friend class `Engine` that has access to private members of `Input`.
     */
    friend class Engine;

private:
    CursorPos _cursor_pos{}; ///< The current position of the cursor.
    std::array<bool, mouse_button_enumerations.size()> _mouse_button_states{}; ///< Array storing the states of mouse buttons.
    std::array<bool, key_enumerations.size()> _key_states{}; ///< Array storing the states of keyboard keys.

private:
    /**
     * @brief Sets the cursor position.
     * 
     * @param cursor_pos The new cursor position.
     */
    void set_cursor_pos(const CursorPos& cursor_pos);

    /**
     * @brief Sets the state of a specific mouse button (pressed or not).
     * 
     * @param button The mouse button to update.
     * @param value The state to set for the button (`true` for pressed, `false` for not pressed).
     */
    void set_mouse_button_pressed(MouseButton button, bool value);

    /**
     * @brief Sets the state of a specific key (pressed or not).
     * 
     * @param key The key to update.
     * @param value The state to set for the key (`true` for pressed, `false` for not pressed).
     */
    void set_key_pressed(Key key, bool value);

    /**
     * @brief Retrieves the index of a given mouse button in the internal state array.
     * 
     * @param button The mouse button.
     * @return The index of the mouse button in the array.
     */
    usize get_index(MouseButton button) const;

    /**
     * @brief Retrieves the index of a given key in the internal state array.
     * 
     * @param key The key.
     * @return The index of the key in the array.
     */
    usize get_index(Key key) const;
};

} // namespace zth
