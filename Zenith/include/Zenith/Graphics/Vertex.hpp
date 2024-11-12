#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>

#include "Zenith/Graphics/Color.hpp"
#include "Zenith/Math/Vec2.hpp"

namespace zth {

struct Vertex
{
    Vec2f position;
    Color color = Color::white;
    Vec2f tex_coords = { 0.0f, 0.0f };

    explicit operator sf::Vertex() const
    {
        return { static_cast<sf::Vector2f>(position), static_cast<sf::Color>(color),
                 static_cast<sf::Vector2f>(tex_coords) };
    }
};

} // namespace zth
