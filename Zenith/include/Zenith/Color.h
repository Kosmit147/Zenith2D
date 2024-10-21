#pragma once

#include <SFML/Graphics/Color.hpp>

#include "Typedefs.h"

namespace zth {

struct Color
{
    u8 r;
    u8 g;
    u8 b;
    u8 a;

    static const Color Black;
    static const Color White;
    static const Color Red;
    static const Color Green;
    static const Color Blue;
    static const Color Yellow;
    static const Color Magenta;
    static const Color Cyan;
    static const Color Transparent;

    explicit inline operator sf::Color() const { return sf::Color{ r, g, b, a }; }
};

inline const Color Color::Black = { 0, 0, 0, 255 };
inline const Color Color::White = { 255, 255, 255, 255 };
inline const Color Color::Red = { 255, 0, 0, 255 };
inline const Color Color::Green = { 0, 255, 0, 255 };
inline const Color Color::Blue = { 0, 0, 255, 255 };
inline const Color Color::Yellow = { 255, 255, 0, 255 };
inline const Color Color::Magenta = { 255, 0, 255, 255 };
inline const Color Color::Cyan = { 0, 255, 255, 255 };
inline const Color Color::Transparent = { 0, 0, 0, 0 };

} // namespace zth
