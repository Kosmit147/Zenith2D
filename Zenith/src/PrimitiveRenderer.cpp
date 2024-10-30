#include "PrimitiveRenderer.hpp"

#include <SFML/Graphics.hpp>

#include "Typedefs.hpp"

namespace zth {

void PrimitiveRenderer::draw_point(const Vec2f& point, const Color& color)
{
    sf::Vertex vertex(static_cast<sf::Vector2f>(point), static_cast<sf::Color>(color));
    _render_target.draw(&vertex, 1, sf::Points);
}

void PrimitiveRenderer::draw_line(const Vec2f& from, const Vec2f& to, const Color& color)
{
    switch (rendering_algorithm)
    {
    case RenderingAlgorithm::Sfml:
        _draw_command.mode = sf::Lines;
        break;
    case RenderingAlgorithm::Custom:
        _draw_command.mode = sf::Points;
        break;
    }

    switch (rendering_algorithm)
    {
    case RenderingAlgorithm::Sfml:
        draw_line_sfml(from, to, color);
        break;
    case RenderingAlgorithm::Custom:
        draw_line_custom(from, to, color);
        break;
    }

    _draw_command.execute(_target);
}

void PrimitiveRenderer::draw_line(const Line& line, const Color& color)
{
    draw_line(line.from, line.to, color);
}

void PrimitiveRenderer::draw_lines(std::span<const Vec2f> points, const Color& color)
{
    switch (rendering_algorithm)
    {
    case RenderingAlgorithm::Sfml:
        _draw_command.mode = sf::Lines;
        break;
    case RenderingAlgorithm::Custom:
        _draw_command.mode = sf::Points;
        break;
    }

    for (const auto line : points | std::views::adjacent<2>)
    {
        const auto& [from, to] = line;

        switch (rendering_algorithm)
        {
        case RenderingAlgorithm::Sfml:
            draw_line_sfml(from, to, color);
            break;
        case RenderingAlgorithm::Custom:
            draw_line_custom(from, to, color);
            break;
        }
    }

    _draw_command.execute(_target);
}

void PrimitiveRenderer::draw_lines(std::span<const Line> lines, const Color& color)
{
    switch (rendering_algorithm)
    {
    case RenderingAlgorithm::Sfml:
        _draw_command.mode = sf::Lines;
        break;
    case RenderingAlgorithm::Custom:
        _draw_command.mode = sf::Points;
        break;
    }

    for (const auto line : lines)
    {
        const auto& [from, to] = line;

        switch (rendering_algorithm)
        {
        case RenderingAlgorithm::Sfml:
            draw_line_sfml(from, to, color);
            break;
        case RenderingAlgorithm::Custom:
            draw_line_custom(from, to, color);
            break;
        }
    }

    _draw_command.execute(_target);
}

void PrimitiveRenderer::draw_closed_lines(std::span<const Vec2f> points, const Color& color)
{
    if (points.size() < 2)
        return;

    for (const auto line : points | std::views::adjacent<2>)
    {
        const auto& [from, to] = line;
        draw_line(from, to, color);
    }

    if (points.size() < 3)
        return;

    Line closing_line{ points.front(), points.back() };
    draw_line(closing_line, color);
}

void PrimitiveRenderer::draw_closed_lines(std::span<const Line> lines, const Color& color) const
{
    for (auto& line : lines)
        draw_line(line, color);

    if (lines.size() < 2)
        return;

    Line closing_line{ lines.front().from, lines.back().to };
    draw_line(closing_line, color);
}

void PrimitiveRenderer::draw_rect(const Rect& rect, const Color& color) const
{
    switch (rendering_algorithm)
    {
    case RenderingAlgorithm::Sfml:
        draw_rect_sfml(rect, color);
        break;
    case RenderingAlgorithm::Custom:
        draw_rect_custom(rect, color);
        break;
    }
}

void PrimitiveRenderer::draw_filled_rect(const Rect& rect, const Color& outline_color, const Color& fill_color) const
{
    switch (rendering_algorithm)
    {
    case RenderingAlgorithm::Sfml:
        draw_rect_sfml(rect, outline_color, fill_color);
        break;
    case RenderingAlgorithm::Custom:
        // TODO
        break;
    }
}

static bool is_a_valid_polygon(std::span<const Vec2f> points)
{
    // check if any lines intersect each other
    for (usize i = 0; i < points.size() - 1; i++)
    {
        for (usize j = i + 1; j < points.size() - 1; j++)
        {
            if (lines_intersect({ points[i], points[i + 1] }, { points[j], points[j + 1] }))
                return false;
        }
    }

    return true;
}

static bool is_a_valid_polygon(std::span<const Line> lines)
{
    // make sure the lines connect to each other
    for (usize i = 0; i < lines.size() - 1; i++)
    {
        if (lines[i].to != lines[i + 1].from)
            return false;
    }

    // make sure the last line connects to the first one
    if (lines.back().to != lines.front().from)
        return false;

    // check if any lines intersect each other
    for (usize i = 0; i < lines.size() - 1; i++)
    {
        for (usize j = i + 1; j < lines.size(); j++)
        {
            if (lines_intersect(lines[i], lines[j]))
                return false;
        }
    }

    return true;
}

void PrimitiveRenderer::draw_polygon(std::span<const Vec2f> points, const Color& color) const
{
    if (points.size() < 2)
        return;

    if (!is_a_valid_polygon(points))
        return;

    switch (rendering_algorithm)
    {
    case RenderingAlgorithm::Sfml:
        draw_polygon_sfml(points, color);
        break;
    case RenderingAlgorithm::Custom:
        draw_polygon_custom(points, color);
        break;
    }
}

void PrimitiveRenderer::draw_polygon(std::span<const Line> lines, const Color& color) const
{
    if (lines.empty())
        return;

    if (!is_a_valid_polygon(lines))
        return;

    switch (rendering_algorithm)
    {
    case RenderingAlgorithm::Sfml:
        draw_polygon_sfml(lines, color);
        break;
    case RenderingAlgorithm::Custom:
        draw_polygon_custom(lines, color);
        break;
    }
}

void PrimitiveRenderer::draw_filled_polygon(std::span<const Vec2f> points, const Color& outline_color,
                                            const Color& fill_color) const
{
    if (points.size() < 2)
        return;

    if (!is_a_valid_polygon(points))
        return;

    switch (rendering_algorithm)
    {
    case RenderingAlgorithm::Sfml:
        draw_polygon_sfml(points, outline_color, fill_color);
        break;
    case RenderingAlgorithm::Custom:
        draw_filled_polygon_custom(points, outline_color, fill_color);
        break;
    }
}

void PrimitiveRenderer::draw_filled_polygon(std::span<const Line> lines, const Color& outline_color,
                                            const Color& fill_color)
{
    if (lines.empty())
        return;

    if (!is_a_valid_polygon(lines))
        return;

    switch (rendering_algorithm)
    {
    case RenderingAlgorithm::Sfml:
        draw_polygon_sfml(lines, outline_color, fill_color);
        break;
    case RenderingAlgorithm::Custom:
        draw_filled_polygon_custom(lines, outline_color, fill_color);
        break;
    }
}

void PrimitiveRenderer::draw_circle(const Circle& circle, const Color& color) const
{
    switch (rendering_algorithm)
    {
    case RenderingAlgorithm::Sfml:
        draw_circle_sfml(circle, color);
        break;
    case RenderingAlgorithm::Custom:
        draw_circle_custom(circle, color);
        break;
    }
}

void PrimitiveRenderer::draw_filled_circle(const Circle& circle, const Color& outline_color,
                                           const Color& fill_color) const
{
    switch (rendering_algorithm)
    {
    case RenderingAlgorithm::Sfml:
        draw_circle_sfml(circle, outline_color, fill_color);
        break;
    case RenderingAlgorithm::Custom:
        // TODO
        break;
    }
}

void PrimitiveRenderer::draw_ellipse(const Ellipse& ellipse, const Color& color) const
{
    switch (rendering_algorithm)
    {
    case RenderingAlgorithm::Sfml:
        draw_ellipse_sfml(ellipse, color);
        break;
    case RenderingAlgorithm::Custom:
        draw_ellipse_custom(ellipse, color);
        break;
    }
}

void PrimitiveRenderer::draw_filled_ellipse(const Ellipse& ellipse, const Color& outline_color,
                                            const Color& fill_color) const
{
    switch (rendering_algorithm)
    {
    case RenderingAlgorithm::Sfml:
        draw_ellipse_sfml(ellipse, outline_color, fill_color);
        break;
    case RenderingAlgorithm::Custom:
        // TODO
        break;
    }
}

} // namespace zth
