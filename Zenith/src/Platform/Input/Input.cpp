#include "Zenith/Platform/Input/Input.hpp"

namespace zth {

CursorPos Input::cursor_pos() const
{
    return _cursor_pos;
}

bool Input::is_mouse_button_pressed(MouseButton button) const
{
    return _mouse_button_states[get_index(button)];
}

bool Input::is_key_pressed(Key key) const
{
    return _key_states[get_index(key)];
}

void Input::set_cursor_pos(const CursorPos& cursor_pos)
{
    _cursor_pos = cursor_pos;
}

void Input::set_mouse_button_pressed(MouseButton button, bool value)
{
    _mouse_button_states[get_index(button)] = value;
}

void Input::set_key_pressed(Key key, bool value)
{
    _key_states[get_index(key)] = value;
}

usize Input::get_index(MouseButton button) const
{
    usize index = static_cast<usize>(button);
    assert(index < _mouse_button_states.size());
    return index;
}

usize Input::get_index(Key key) const
{
    usize index = static_cast<usize>(key) + 1;
    assert(index < _key_states.size());
    return index;
}

} // namespace zth
