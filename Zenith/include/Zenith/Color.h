#pragma once

#include <SFML/Graphics/Color.hpp>

#include <cstdint>

namespace zth {

struct Color
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;

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
