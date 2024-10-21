#include "PrimitiveRenderer.hpp"

#include <SFML/Graphics.hpp>

#include "EllipseShape.hpp"
#include "Typedefs.hpp"
#include "Window.hpp"

namespace zth {

void PrimitiveRenderer::draw(Point2D point, const Color& color)
{
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

void PrimitiveRenderer::draw_closed_lines(std::span<const Line> lines, const Color& color,
                                          RenderingAlgorithm alg)
{
    for (const auto& line : lines)
        draw(line, color, alg);

    if (lines.size() < 2)
        return;

    Line closing_line{ lines.front().from, lines.back().to };
    draw(closing_line, color, alg);
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
    const auto sf_color = static_cast<sf::Color>(color);

    auto [delta_x, delta_y] = line.to - line.from;
    float slope = delta_y / delta_x;

    if (slope > 1.0f || slope < -1.0f)
    {
        // we're drawing a point for every y coord and calculating the appropriate x coord
        slope = 1.0f / slope;

        const auto& [start_point, end_point] =
            std::minmax(line.from, line.to, [](auto& from, auto& to) { return from.y <= to.y; });

        float x = start_point.x;
        i32 y = static_cast<i32>(start_point.y);
        i32 end_y = static_cast<i32>(end_point.y);
        assert(y <= end_y);

        std::vector<sf::Vertex> vertices;
        vertices.reserve(static_cast<usize>(end_y - y + 1));

        for (; y <= end_y; y++)
        {
            x += slope;
            vertices.emplace_back(sf::Vector2f{ x, static_cast<float>(y) }, sf_color);
        }

        _window->sf_window().draw(vertices.data(), vertices.size(), sf::Points);
    }
    else
    {
        // we're drawing a point for every x coord and calculating the appropriate y coord
        const auto& [start_point, end_point] =
            std::minmax(line.from, line.to, [](auto& from, auto& to) { return from.x <= to.x; });

        i32 x = static_cast<i32>(start_point.x);
        i32 end_x = static_cast<i32>(end_point.x);
        float y = start_point.y;
        assert(x <= end_x);

        std::vector<sf::Vertex> vertices;
        vertices.reserve(static_cast<usize>(end_x - x + 1));

        for (; x <= end_x; x++)
        {
            y += slope;
            vertices.emplace_back(sf::Vector2f{ static_cast<float>(x), y }, sf_color);
        }

        _window->sf_window().draw(vertices.data(), vertices.size(), sf::Points);
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
    constexpr auto pi = std::numbers::pi_v<float>;
    const auto sf_color = static_cast<sf::Color>(color);

    auto [xc, yc] = circle.center;
    float step = 1.0f / circle.radius;

    for (float alpha = 0; alpha < pi / 4.0f; alpha += step)
    {
        float x = circle.radius * std::cos(alpha);
        float y = circle.radius * std::sin(alpha);

        std::array<sf::Vertex, 8> vertices = {
            sf::Vertex{ { xc + x, yc + y }, sf_color }, sf::Vertex{ { xc + x, yc - y }, sf_color },
            sf::Vertex{ { xc - x, yc + y }, sf_color }, sf::Vertex{ { xc - x, yc - y }, sf_color },
            sf::Vertex{ { xc + y, yc + x }, sf_color }, sf::Vertex{ { xc + y, yc - x }, sf_color },
            sf::Vertex{ { xc - y, yc + x }, sf_color }, sf::Vertex{ { xc - y, yc - x }, sf_color },
        };

        _window->sf_window().draw(vertices.data(), vertices.size(), sf::Points);
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
    constexpr auto pi = std::numbers::pi_v<float>;
    const auto sf_color = static_cast<sf::Color>(color);

    auto [xc, yc] = ellipse.center;
    float step = 1.0f / std::max(ellipse.radius.x, ellipse.radius.y);

    for (float alpha = 0; alpha < pi / 2.0f; alpha += step)
    {
        float x = ellipse.radius.x * std::cos(alpha);
        float y = ellipse.radius.y * std::sin(alpha);

        std::array<sf::Vertex, 4> vertices = {
            sf::Vertex{ { xc + x, yc + y }, sf_color },
            sf::Vertex{ { xc + x, yc - y }, sf_color },
            sf::Vertex{ { xc - x, yc + y }, sf_color },
            sf::Vertex{ { xc - x, yc - y }, sf_color },
        };

        _window->sf_window().draw(vertices.data(), vertices.size(), sf::Points);
    }
}

} // namespace zth
