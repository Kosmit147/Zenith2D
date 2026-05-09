/**
 * @file Vertex.hpp
 * @brief Defines the `Vertex` struct for representing a vertex in 2D space with position, color, and texture coordinates.
 * 
 * This file provides the `Vertex` struct, which is used to define a vertex in the 2D graphics system.
 * The vertex contains a position, color, and texture coordinates. It also includes an explicit operator 
 * to convert the `Vertex` to an `sf::Vertex` for use with SFML rendering.
 */

#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>

#include "Zenith/Graphics/Color.hpp"
#include "Zenith/Math/Vec2.hpp"

namespace zth {

/**
 * @struct Vertex
 * @brief Represents a vertex with a position, color, and texture coordinates.
 * 
 * A vertex is a fundamental component used in rendering 2D objects. It includes:
 * - Position in 2D space (`position`).
 * - Color (`color`).
 * - Texture coordinates (`tex_coords`), used for mapping textures to vertices.
 */
struct Vertex
{
    Vec2f position; ///< The position of the vertex in 2D space.
    Color color = Color::white; ///< The color of the vertex. Default is white.
    Vec2f tex_coords = { 0.0f, 0.0f }; ///< The texture coordinates. Default is (0.0, 0.0).

    /**
     * @brief Converts the `Vertex` to an `sf::Vertex`.
     * 
     * This operator allows implicit conversion from `Vertex` to `sf::Vertex`, 
     * which is used in SFML's rendering system.
     * 
     * @return The equivalent `sf::Vertex` representation.
     */
    explicit operator sf::Vertex() const
    {
        return { static_cast<sf::Vector2f>(position), static_cast<sf::Color>(color),
                 static_cast<sf::Vector2f>(tex_coords) };
    }
};

} // namespace zth
