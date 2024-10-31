#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

namespace zth {

struct DrawCall
{
    std::vector<sf::Vertex> vertices = {};

    void execute(sf::RenderTarget& render_target, sf::PrimitiveType mode)
    {
        render_target.draw(vertices.data(), vertices.size(), mode);
        clear();
    }

    void clear() { vertices.clear(); }
};

} // namespace zth
