#pragma once

#include "Keyboard.hpp"
#include "Mouse.hpp"
#include "Zenith/Core/Typedefs.hpp"

namespace zth {

class Input
{
public:
    CursorPos cursor_pos() const;
    bool is_mouse_button_pressed(MouseButton button) const;
    bool is_key_pressed(Key key) const;

    friend class Application;

private:
    CursorPos _cursor_pos{};
    std::array<bool, mouse_button_enumerations.size()> _mouse_button_states{};
    std::array<bool, key_enumerations.size()> _key_states{};

private:
    void set_cursor_pos(const CursorPos& cursor_pos);
    void set_mouse_button_pressed(MouseButton button, bool value);
    void set_key_pressed(Key key, bool value);

    usize get_index(MouseButton button) const;
    usize get_index(Key key) const;
};

} // namespace zth
