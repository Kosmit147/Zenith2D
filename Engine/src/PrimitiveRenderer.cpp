#include "PrimitiveRenderer.h"

#include <math.h>

void PrimitiveRenderer::draw(Point2D point)
{
    sf::RectangleShape drawable;
    sf::Vertex vertex({ point.x, point.y }, sf::Color::Green);
    _window->draw(&vertex, 1, sf::Points);
}

void PrimitiveRenderer::draw(const Line& line, LineRenderingAlgorithm alg)
{
    if (alg == LineRenderingAlgorithm::Incremental)
    {

        float m = (line.to.y - line.from.y) / (line.to.x - line.from.x);

        if (m > 1.0f)
        {
            m = (line.to.x - line.from.x) / (line.to.y - line.from.y);
            float x = line.from.x;

            for (int y = line.from.y; y < line.to.y; y++)
            {
                x += m;
                draw(Point2D{ std::round(x), (float)y });
            }
        }
        else
        {
            float y = line.from.y;

            for (int x = line.from.x; x < line.to.x; x++)
            {
                y += m;
                draw(Point2D{ (float)x, std::round(y) });
            }
        }
    }
    else if (alg == LineRenderingAlgorithm::Default)
    {
        sf::Vertex drawable[] = { sf::Vertex(sf::Vector2f(line.from.x, line.from.y)),
                                  sf::Vertex(sf::Vector2f(line.to.x, line.to.y)) };

        _window->draw(drawable, 2, sf::Lines);
    }
}

void PrimitiveRenderer::draw(std::span<Line> lines, LineRenderingAlgorithm alg)
{
    for (auto& line : lines)
        draw(line, alg);
}
