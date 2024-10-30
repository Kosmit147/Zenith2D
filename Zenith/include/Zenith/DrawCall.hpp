#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

namespace zth {

struct DrawCall
{
    std::vector<sf::Vertex> vertices;
    sf::PrimitiveType mode;

    void execute(sf::RenderTarget& target)
    {
        target.draw(vertices.data(), vertices.size(), mode);
        clear();
    }

    void clear() { vertices.clear(); }
};

} // namespace zth
