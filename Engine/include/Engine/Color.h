#pragma once

#include <SFML/Graphics/Color.hpp>

#include <cstdint>

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