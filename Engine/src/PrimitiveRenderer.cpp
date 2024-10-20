#include "PrimitiveRenderer.h"

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <numbers>

#include "EllipseShape.h"
#include "Window.h"

void PrimitiveRenderer::draw(Point2D point, const Color& color)
{
    sf::RectangleShape drawable;
    sf::Vertex vertex(static_cast<sf::Vector2f>(point), static_cast<sf::Color>(color));
    _window->sf_window().draw(&vertex, 1, sf::Points);
}

void PrimitiveRenderer::draw(const Line& line, const Color& color, RenderingAlgorithm alg)
{
    switch (alg)
    {
    case RenderingAlgorithm::SFML:
        draw_line_sfml(line, color);
        break;
    case RenderingAlgorithm::Custom:
        draw_line_custom(line, color);
        break;
    }
}

void PrimitiveRenderer::draw(std::span<const Line> lines, const Color& color, RenderingAlgorithm alg)
{
    for (const auto& line : lines)
        draw(line, color, alg);
}

void PrimitiveRenderer::draw(const Circle& circle, const Color& color, RenderingAlgorithm alg)
{
    switch (alg)
    {
    case RenderingAlgorithm::SFML:
        draw_circle_sfml(circle, color);
        break;
    case RenderingAlgorithm::Custom:
        draw_circle_custom(circle, color);
        break;
    }
}

void PrimitiveRenderer::draw(const Ellipse& ellipse, const Color& color, RenderingAlgorithm alg)
{
    switch (alg)
    {
    case RenderingAlgorithm::SFML:
        draw_ellipse_sfml(ellipse, color);
        break;
    case RenderingAlgorithm::Custom:
        draw_ellipse_custom(ellipse, color);
        break;
    }
}

void PrimitiveRenderer::draw_line_sfml(const Line& line, const Color& color)
{
    sf::Vertex sf_line[] = {
        sf::Vertex{ static_cast<sf::Vector2f>(line.from), static_cast<sf::Color>(color) },
        sf::Vertex{ static_cast<sf::Vector2f>(line.to), static_cast<sf::Color>(color) }
    };

    _window->sf_window().draw(sf_line, 2, sf::Lines);
}

void PrimitiveRenderer::draw_line_custom(const Line& line, const Color& color)
{
    auto [delta_x, delta_y] = line.to - line.from;
    float slope = delta_y / delta_x;

    if (slope > 1.0f || slope < -1.0f)
    {
        // we're drawing a point for every y coord and calculating the appropriate x coord
        slope = 1.0f / slope;

        const auto& [start_point, end_point] =
            std::minmax(line.from, line.to, [](auto& from, auto& to) { return from.y < to.y; });

        float x = start_point.x;
        int32_t y = static_cast<int32_t>(start_point.y);
        auto end_y = static_cast<int32_t>(end_point.y);

        for (; y <= end_y; y++)
        {
            x += slope;
            draw(Point2D{ x, static_cast<float>(y) }, color);
        }
    }
    else
    {
        // we're drawing a point for every x coord and calculating the appropriate y coord
        const auto& [start_point, end_point] =
            std::minmax(line.from, line.to, [](auto& from, auto& to) { return from.x < to.x; });

        int32_t x = static_cast<int32_t>(start_point.x);
        auto end_x = static_cast<int32_t>(end_point.x);
        float y = start_point.y;

        for (; x <= end_x; x++)
        {
            y += slope;
            draw(Point2D{ static_cast<float>(x), y }, color);
        }
    }
}

void PrimitiveRenderer::draw_circle_sfml(const Circle& circle, const Color& color)
{
    sf::CircleShape sf_circle;
    sf_circle.setRadius(circle.radius);
    sf_circle.setOutlineColor(static_cast<sf::Color>(color));
    sf_circle.setFillColor(static_cast<sf::Color>(Color::Transparent));
    sf_circle.setOutlineThickness(1);
    sf_circle.setPosition(static_cast<sf::Vector2f>(circle.center - Point2D{ circle.radius, circle.radius }));

    _window->sf_window().draw(sf_circle);
}

void PrimitiveRenderer::draw_circle_custom(const Circle& circle, const Color& color)
{
    auto [xc, yc] = circle.center;
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

void PrimitiveRenderer::draw_ellipse_sfml(const Ellipse& ellipse, const Color& color)
{
    EllipseShape sf_ellipse(ellipse);
    sf_ellipse.setOutlineColor(static_cast<sf::Color>(color));
    sf_ellipse.setFillColor(static_cast<sf::Color>(Color::Transparent));
    sf_ellipse.setOutlineThickness(1);

    _window->sf_window().draw(sf_ellipse);
}

void PrimitiveRenderer::draw_ellipse_custom(const Ellipse& ellipse, const Color& color)
{
    auto [xc, yc] = ellipse.center;
    float step = 1.0f / std::max(ellipse.radius.x, ellipse.radius.y);

    for (float alpha = 0; alpha < std::numbers::pi / 2.0f; alpha += step)
    {
        float x = ellipse.radius.x * std::cos(alpha);
        float y = ellipse.radius.y * std::sin(alpha);

        draw(Point2D{ xc + x, yc + y }, color);
        draw(Point2D{ xc + x, yc - y }, color);
        draw(Point2D{ xc - x, yc + y }, color);
        draw(Point2D{ xc - x, yc - y }, color);
    }
}
