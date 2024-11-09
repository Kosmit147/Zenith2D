#include "Zenith/Platform/Input/Mouse.hpp"

namespace zth {

MouseButton to_mouse_button(sf::Mouse::Button button)
{
    switch (button)
    {
    case sf::Mouse::Button::Left:
        return MouseButton::Left;
    case sf::Mouse::Button::Right:
        return MouseButton::Right;
    case sf::Mouse::Button::Middle:
    case sf::Mouse::Button::XButton1:
    case sf::Mouse::Button::XButton2:
    case sf::Mouse::Button::ButtonCount:
        break;
    }

    assert(false);
    std::unreachable();
}

const char* to_string(MouseButton button)
{
    switch (button)
    {
        using enum MouseButton;
    case Left:
        return "Left";
    case Right:
        return "Right";
    }

    assert(false);
    return "Unknown";
}

} // namespace zth
