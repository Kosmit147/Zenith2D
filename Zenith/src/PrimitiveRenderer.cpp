#include "PrimitiveRenderer.hpp"

#include <SFML/Graphics.hpp>

#include "EllipseShape.hpp"
#include "Typedefs.hpp"
#include "Window.hpp"

namespace zth {

void PrimitiveRenderer::draw_point(Point2D point, const Color& color) const
{
    sf::Vertex vertex(static_cast<sf::Vector2f>(point), static_cast<sf::Color>(color));
    _window.draw(&vertex, 1, sf::Points);
}

void PrimitiveRenderer::draw_line(const Point2D& from, const Point2D& to, const Color& color) const
{
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

void PrimitiveRenderer::draw_line(const Line& line, const Color& color) const
{
    draw_line(line.from, line.to, color);
}

void PrimitiveRenderer::draw_lines(std::span<const Point2D> points, const Color& color) const
{
    for (const auto line : points | std::views::adjacent<2>)
    {
        const auto& [from, to] = line;
        draw_line(from, to, color);
    }
}

void PrimitiveRenderer::draw_lines(std::span<const Line> lines, const Color& color) const
{
    for (const auto& line : lines)
        draw_line(line, color);
}

void PrimitiveRenderer::draw_closed_lines(std::span<const Point2D> points, const Color& color) const
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
        // TODO
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

static bool is_a_valid_polygon(std::span<const Point2D> points)
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

void PrimitiveRenderer::draw_polygon(std::span<const Point2D> points, const Color& color) const
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

void PrimitiveRenderer::draw_filled_polygon(std::span<const Point2D> points, const Color& outline_color,
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
        // TODO
        break;
    }
}

void PrimitiveRenderer::draw_filled_polygon(std::span<const Line> lines, const Color& outline_color,
                                            const Color& fill_color) const
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
        // TODO
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

void PrimitiveRenderer::draw_line_sfml(const Point2D& from, const Point2D& to, const Color& color) const
{
    sf::Vertex sf_line[] = { sf::Vertex{ static_cast<sf::Vector2f>(from), static_cast<sf::Color>(color) },
                             sf::Vertex{ static_cast<sf::Vector2f>(to), static_cast<sf::Color>(color) } };

    _window.draw(sf_line, 2, sf::Lines);
}

void PrimitiveRenderer::draw_line_sfml(const Line& line, const Color& color) const
{
    draw_line_sfml(line.from, line.to, color);
}

void PrimitiveRenderer::draw_line_custom(const Point2D& from, const Point2D& to, const Color& color) const
{
    const auto sf_color = static_cast<sf::Color>(color);

    auto [delta_x, delta_y] = to - from;
    float slope = delta_y / delta_x;

    if (slope > 1.0f || slope < -1.0f)
    {
        // we're drawing a point for every y coord and calculating the corresponding x coord
        slope = 1.0f / slope;

        const auto& [start_point, end_point] =
            std::minmax(from, to, [](auto& from, auto& to) { return from.y <= to.y; });

        float x = start_point.x;
        i32 y = static_cast<i32>(start_point.y);
        i32 end_y = static_cast<i32>(end_point.y);
        assert(y <= end_y);

        std::vector<sf::Vertex> vertices;
        vertices.reserve(end_y - y + 1);

        for (; y <= end_y; y++)
        {
            x += slope;
            vertices.emplace_back(sf::Vector2f{ x, static_cast<float>(y) }, sf_color);
        }

        _window.draw(vertices.data(), vertices.size(), sf::Points);
    }
    else
    {
        // we're drawing a point for every x coord and calculating the corresponding y coord
        const auto& [start_point, end_point] =
            std::minmax(from, to, [](auto& from, auto& to) { return from.x <= to.x; });

        i32 x = static_cast<i32>(start_point.x);
        i32 end_x = static_cast<i32>(end_point.x);
        float y = start_point.y;
        assert(x <= end_x);

        std::vector<sf::Vertex> vertices;
        vertices.reserve(end_x - x + 1);

        for (; x <= end_x; x++)
        {
            y += slope;
            vertices.emplace_back(sf::Vector2f{ static_cast<float>(x), y }, sf_color);
        }

        _window.draw(vertices.data(), vertices.size(), sf::Points);
    }
}

void PrimitiveRenderer::draw_line_custom(const Line& line, const Color& color) const
{
    draw_line_custom(line.from, line.to, color);
}

void PrimitiveRenderer::draw_rect_sfml(const Rect& rect, const Color& outline_color, const Color& fill_color) const
{
    sf::RectangleShape sf_rectangle;
    sf_rectangle.setSize(static_cast<sf::Vector2f>(rect.size));
    sf_rectangle.setOutlineColor(static_cast<sf::Color>(outline_color));
    sf_rectangle.setOutlineThickness(1);
    sf_rectangle.setFillColor(static_cast<sf::Color>(fill_color));
    sf_rectangle.setPosition(static_cast<sf::Vector2f>(rect.position));

    _window.draw(sf_rectangle);
}

void PrimitiveRenderer::draw_polygon_sfml(std::span<const Point2D> points, const Color& outline_color,
                                          const Color& fill_color) const
{
    sf::ConvexShape sf_polygon;
    sf_polygon.setPointCount(points.size());

    for (usize i = 0; i < points.size(); i++)
        sf_polygon.setPoint(i, static_cast<sf::Vector2f>(points[i]));

    sf_polygon.setOutlineColor(static_cast<sf::Color>(outline_color));
    sf_polygon.setOutlineThickness(1);
    sf_polygon.setFillColor(static_cast<sf::Color>(fill_color));
    _window.draw(sf_polygon);
}

void PrimitiveRenderer::draw_polygon_sfml(std::span<const Line> lines, const Color& outline_color,
                                          const Color& fill_color) const
{
    sf::ConvexShape sf_polygon;
    sf_polygon.setPointCount(lines.size());

    for (usize i = 0; i < lines.size(); i++)
        sf_polygon.setPoint(i, static_cast<sf::Vector2f>(lines[i].from));

    sf_polygon.setOutlineColor(static_cast<sf::Color>(outline_color));
    sf_polygon.setOutlineThickness(1);
    sf_polygon.setFillColor(static_cast<sf::Color>(fill_color));
    _window.draw(sf_polygon);
}

void PrimitiveRenderer::draw_polygon_custom(std::span<const Point2D> points, const Color& outline_color) const
{
    (void)points;
    (void)outline_color;
    // TODO
}

void PrimitiveRenderer::draw_polygon_custom(std::span<const Line> lines, const Color& outline_color) const
{
    (void)lines;
    (void)outline_color;
    // TODO
}

void PrimitiveRenderer::draw_circle_sfml(const Circle& circle, const Color& outline_color,
                                         const Color& fill_color) const
{
    sf::CircleShape sf_circle;
    sf_circle.setRadius(circle.radius);
    sf_circle.setOutlineColor(static_cast<sf::Color>(outline_color));
    sf_circle.setOutlineThickness(1);
    sf_circle.setFillColor(static_cast<sf::Color>(fill_color));
    sf_circle.setPosition(static_cast<sf::Vector2f>(circle.center - Point2D{ circle.radius, circle.radius }));

    _window.draw(sf_circle);
}

void PrimitiveRenderer::draw_circle_custom(const Circle& circle, const Color& color) const
{
    constexpr auto pi = std::numbers::pi_v<float>;
    const auto sf_color = static_cast<sf::Color>(color);

    auto [xc, yc] = circle.center;
    float step = 1.0f / circle.radius;

    // TODO: do something about floating-point loop counter
    for (float alpha = 0; alpha < pi / 4.0f; alpha += step)
    {
        float x = circle.radius * std::cos(alpha);
        float y = circle.radius * std::sin(alpha);

        std::array vertices = {
            sf::Vertex{ { xc + x, yc + y }, sf_color }, sf::Vertex{ { xc + x, yc - y }, sf_color },
            sf::Vertex{ { xc - x, yc + y }, sf_color }, sf::Vertex{ { xc - x, yc - y }, sf_color },
            sf::Vertex{ { xc + y, yc + x }, sf_color }, sf::Vertex{ { xc + y, yc - x }, sf_color },
            sf::Vertex{ { xc - y, yc + x }, sf_color }, sf::Vertex{ { xc - y, yc - x }, sf_color },
        };

        _window.draw(vertices.data(), vertices.size(), sf::Points);
    }
}

void PrimitiveRenderer::draw_ellipse_sfml(const Ellipse& ellipse, const Color& outline_color,
                                          const Color& fill_color) const
{
    EllipseShape sf_ellipse(ellipse);
    sf_ellipse.setOutlineColor(static_cast<sf::Color>(outline_color));
    sf_ellipse.setOutlineThickness(1);
    sf_ellipse.setFillColor(static_cast<sf::Color>(fill_color));

    _window.draw(sf_ellipse);
}

void PrimitiveRenderer::draw_ellipse_custom(const Ellipse& ellipse, const Color& color) const
{
    constexpr auto pi = std::numbers::pi_v<float>;
    const auto sf_color = static_cast<sf::Color>(color);

    auto [xc, yc] = ellipse.center;
    float step = 1.0f / std::max(ellipse.radius.x, ellipse.radius.y);

    // TODO: do something about floating-point loop counter
    for (float alpha = 0; alpha < pi / 2.0f; alpha += step)
    {
        float x = ellipse.radius.x * std::cos(alpha);
        float y = ellipse.radius.y * std::sin(alpha);

        std::array vertices = {
            sf::Vertex{ { xc + x, yc + y }, sf_color },
            sf::Vertex{ { xc + x, yc - y }, sf_color },
            sf::Vertex{ { xc - x, yc + y }, sf_color },
            sf::Vertex{ { xc - x, yc - y }, sf_color },
        };

        _window.draw(vertices.data(), vertices.size(), sf::Points);
    }
}

} // namespace zth
