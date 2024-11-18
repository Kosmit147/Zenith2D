/**
 * @file Color.hpp
 * @brief Declares the Color struct, representing a color with RGBA components.
 */

#pragma once

#include <SFML/Graphics/Color.hpp>

#include "Zenith/Core/Typedefs.hpp"

namespace zth {

/**
 * @struct Color
 * @brief A struct representing a color with red, green, blue, and alpha (RGBA) components.
 *
 * This struct defines a color using 8-bit unsigned integers for the red, green, blue, and alpha channels.
 * It also provides some predefined color constants such as black, white, red, etc., and an explicit
 * conversion operator to SFML's `sf::Color` type.
 */
struct Color
{
    u8 r; ///< Red component of the color (0-255).
    u8 g; ///< Green component of the color (0-255).
    u8 b; ///< Blue component of the color (0-255).
    u8 a; ///< Alpha component of the color (0-255, where 255 is fully opaque).

    /// Predefined constant for the color black.
    static const Color black;
    /// Predefined constant for the color white.
    static const Color white;
    /// Predefined constant for the color red.
    static const Color red;
    /// Predefined constant for the color green.
    static const Color green;
    /// Predefined constant for the color blue.
    static const Color blue;
    /// Predefined constant for the color yellow.
    static const Color yellow;
    /// Predefined constant for the color magenta.
    static const Color magenta;
    /// Predefined constant for the color cyan.
    static const Color cyan;
    /// Predefined constant for a transparent color (alpha = 0).
    static const Color transparent;

    /**
     * @brief Converts the Color to an SFML Color.
     * @return An `sf::Color` equivalent of this Color.
     */
    explicit operator sf::Color() const { return sf::Color{ r, g, b, a }; }
};

// Predefined color constants with standard RGBA values
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
