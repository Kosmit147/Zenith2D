#include "PrimitiveRenderer.h"

#include <algorithm>
#include <cmath>
#include <cstddef>

#include "Window.h"

void PrimitiveRenderer::draw(Point2D point, const Color& color)
{
    sf::RectangleShape drawable;
    sf::Vertex vertex(static_cast<sf::Vector2f>(point), static_cast<sf::Color>(color));
    _window->sf_window().draw(&vertex, 1, sf::Points);
}

void PrimitiveRenderer::draw(const Line& line, const Color& color, LineRenderingAlgorithm alg)
{
    switch (alg)
    {
    case LineRenderingAlgorithm::Default:
        draw_line(line, color);
        break;
    case LineRenderingAlgorithm::Incremental:
        draw_line_incremental(line, color);
        break;
    }
}

void PrimitiveRenderer::draw(std::span<Line> lines, const Color& color, LineRenderingAlgorithm alg)
{
    for (const auto& line : lines)
        draw(line, color, alg);
}

void PrimitiveRenderer::draw_line(const Line& line, const Color& color)
{
    sf::Vertex drawable[] = {
        sf::Vertex{ static_cast<sf::Vector2f>(line.from), static_cast<sf::Color>(color) },
        sf::Vertex{ static_cast<sf::Vector2f>(line.to), static_cast<sf::Color>(color) }
    };

    _window->sf_window().draw(drawable, 2, sf::Lines);
}

void PrimitiveRenderer::draw_line_incremental(const Line& line, const Color& color)
{
    float delta_y = line.to.y - line.from.y;
    float delta_x = line.to.x - line.from.x;
    float slope = delta_y / delta_x;

    if (slope > 1.0f || slope < -1.0f)
    {
        // we're drawing a point for every y coord and calculating the appropriate x coord
        slope = 1.0f / slope;

        const auto& [start_point, end_point] =
            std::minmax(line.from, line.to, [](auto& from, auto& to) { return from.y < to.y; });

        float x = start_point.x;
        int32_t y = static_cast<int32_t>(start_point.y);

        for (size_t i = 0; y < end_point.y; i++)
        {
            x += slope;
            draw(Point2D{ x, static_cast<float>(y) }, color);
            y++;
        }
    }
    else
    {
        // we're drawing a point for every x coord and calculating the appropriate y coord
        const auto& [start_point, end_point] =
            std::minmax(line.from, line.to, [](auto& from, auto& to) { return from.x < to.x; });

        int32_t x = static_cast<int32_t>(start_point.x);
        float y = start_point.y;

        for (size_t i = 0; x < end_point.x; i++)
        {
            y += slope;
            draw(Point2D{ static_cast<float>(x), y }, color);
            x++;
        }
    }
}
