#pragma once

#include <SFML/Graphics/Color.hpp>

#include "Zenith/Core/Typedefs.hpp"

namespace zth {

struct Color
{
    u8 r;
    u8 g;
    u8 b;
    u8 a;

    static const Color black;
    static const Color white;
    static const Color red;
    static const Color green;
    static const Color blue;
    static const Color yellow;
    static const Color magenta;
    static const Color cyan;
    static const Color transparent;

    explicit operator sf::Color() const { return sf::Color{ r, g, b, a }; }
};

inline const Color Color::black = { 0, 0, 0, 255 };
inline const Color Color::white = { 255, 255, 255, 255 };
inline const Color Color::red = { 255, 0, 0, 255 };
inline const Color Color::green = { 0, 255, 0, 255 };
inline const Color Color::blue = { 0, 0, 255, 255 };
inline const Color Color::yellow = { 255, 255, 0, 255 };
inline const Color Color::magenta = { 255, 0, 255, 255 };
inline const Color Color::cyan = { 0, 255, 255, 255 };
inline const Color Color::transparent = { 0, 0, 0, 0 };

} // namespace zth
