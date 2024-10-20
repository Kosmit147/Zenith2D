#include "PrimitiveRenderer.h"

#include <algorithm>
#include <cmath>
#include <numbers>

void PrimitiveRenderer::draw(Point2D point, const Color& color)
{
    sf::RectangleShape drawable;
    sf::Vertex vertex({ point.x, point.y }, static_cast<sf::Color>(color));
    _window->sf_window().draw(&vertex, 1, sf::Points);
}

void PrimitiveRenderer::draw(const Line& line, const Color& color, RenderingAlgorithm alg)
{
    if (alg == RenderingAlgorithm::Custom)
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
    else if (alg == RenderingAlgorithm::SFML)
    {
        sf::Vertex drawable[] = {
            sf::Vertex{ static_cast<sf::Vector2f>(line.from), static_cast<sf::Color>(color) },
            sf::Vertex{ static_cast<sf::Vector2f>(line.to), static_cast<sf::Color>(color) }
        };

        _window->sf_window().draw(drawable, 2, sf::Lines);
    }
}

void PrimitiveRenderer::draw(std::span<Line> lines, const Color& color, RenderingAlgorithm alg)
{
    for (const auto& line : lines)
        draw(line, color, alg);
}

void PrimitiveRenderer::draw(const Circle& circle, const Color& color, [[maybe_unused]] RenderingAlgorithm alg)
{
    float xc = circle.center.x;
    float yc = circle.center.y;
    float step = 1.0f / circle.radius;

    for (float alpha = 0; alpha < std::numbers::pi / 4.0f; alpha += step)
    {
        float x = circle.radius * std::cos(alpha);
        float y = circle.radius * std::sin(alpha);

        draw(Point2D{ xc + x, yc + y }, color);
        draw(Point2D{ xc + x, yc - y }, color);
        draw(Point2D{ xc - x, yc + y }, color);
        draw(Point2D{ xc - x, yc - y }, color);
        draw(Point2D{ xc + y, yc + x }, color);
        draw(Point2D{ xc + y, yc - x }, color);
        draw(Point2D{ xc - y, yc + x }, color);
        draw(Point2D{ xc - y, yc - x }, color);
    }
}

void PrimitiveRenderer::draw(const Ellipse& ellipse, const Color& color, [[maybe_unused]] RenderingAlgorithm alg)
{
    float xc = ellipse.center.x;
    float yc = ellipse.center.y;
    float step = 1.0f / std::max(ellipse.radius_x, ellipse.radius_y);

    for (float alpha = 0; alpha < std::numbers::pi / 2.0f; alpha += step)
    {
        float x = ellipse.radius_x * std::cos(alpha);
        float y = ellipse.radius_y * std::sin(alpha);

        draw(Point2D{ xc + x, yc + y }, color);
        draw(Point2D{ xc + x, yc - y }, color);
        draw(Point2D{ xc - x, yc + y }, color);
        draw(Point2D{ xc - x, yc - y }, color);
    }
}
