#pragma once

#include <SFML/Window/Mouse.hpp>

#include <array>

#include "Zenith/Core/Typedefs.hpp"

namespace zth {

struct CursorPos
{
    i32 x;
    i32 y;
};

enum class MouseButton : i8
{
    Left,
    Right,
};

inline constexpr std::array mouse_button_enumerations = {
    MouseButton::Left,
    MouseButton::Right,
};

MouseButton to_mouse_button(sf::Mouse::Button button);
const char* to_string(MouseButton button);

} // namespace zth
