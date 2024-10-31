#include "SfmlPrimitiveRenderer.hpp"

#include "EllipseShape.hpp"
#include "Typedefs.hpp"

namespace zth {

void SfmlPrimitiveRenderer::draw_point(const Vec2f& point, const Color& color)
{
    plot_point(point, color);
    _draw_call.execute(_render_target, sf::Points);
}

void SfmlPrimitiveRenderer::draw_points(std::span<const Vec2f> points, const Color& color)
{
    plot_points(points, color);
    _draw_call.execute(_render_target, sf::Points);
}

void SfmlPrimitiveRenderer::draw_line(const Vec2f& from, const Vec2f& to, const Color& color)
{
    plot_line(from, to, color);
    _draw_call.execute(_render_target, sf::Lines);
}

void SfmlPrimitiveRenderer::draw_line(const Line& line, const Color& color)
{
    plot_line(line, color);
    _draw_call.execute(_render_target, sf::Lines);
}

void SfmlPrimitiveRenderer::draw_line_strip(std::span<const Vec2f> points, const Color& color)
{
    plot_line_strip(points, color);
    _draw_call.execute(_render_target, sf::LineStrip);
}

void SfmlPrimitiveRenderer::draw_lines(std::span<const Line> lines, const Color& color)
{
    plot_lines(lines, color);
    _draw_call.execute(_render_target, sf::Lines);
}

void SfmlPrimitiveRenderer::draw_closed_lines(std::span<const Vec2f> points, const Color& color)
{
    plot_closed_lines(points, color);
    _draw_call.execute(_render_target, sf::LineStrip);
}

void SfmlPrimitiveRenderer::draw_closed_lines(std::span<const Line> lines, const Color& color)
{
    plot_closed_lines(lines, color);
    _draw_call.execute(_render_target, sf::Lines);
}

void SfmlPrimitiveRenderer::draw_rect(const Rect& rect, const Color& color)
{
    plot_rect(rect, color);
    _draw_call.execute(_render_target, sf::LineStrip);
}

void SfmlPrimitiveRenderer::draw_filled_rect(const Rect& rect, const Color& outline_color, const Color& fill_color,
                                             float outline_thickness) const
{
    sf::RectangleShape sf_rectangle;
    sf_rectangle.setSize(static_cast<sf::Vector2f>(rect.size));
    sf_rectangle.setOutlineColor(static_cast<sf::Color>(outline_color));
    sf_rectangle.setOutlineThickness(outline_thickness);
    sf_rectangle.setFillColor(static_cast<sf::Color>(fill_color));
    sf_rectangle.setPosition(static_cast<sf::Vector2f>(rect.position));

    _render_target.draw(sf_rectangle);
}

void SfmlPrimitiveRenderer::draw_polygon(std::span<const Vec2f> points, const Color& color)
{
    plot_polygon(points, color);
    _draw_call.execute(_render_target, sf::LineStrip);
}

void SfmlPrimitiveRenderer::draw_polygon(std::span<const Line> lines, const Color& color)
{
    plot_polygon(lines, color);
    _draw_call.execute(_render_target, sf::Lines);
}

void SfmlPrimitiveRenderer::draw_filled_polygon(std::span<const Vec2f> points, const Color& outline_color,
                                                const Color& fill_color, float outline_thickness) const
{
    sf::ConvexShape sf_polygon;
    sf_polygon.setPointCount(points.size());

    for (usize i = 0; i < points.size(); i++)
        sf_polygon.setPoint(i, static_cast<sf::Vector2f>(points[i]));

    sf_polygon.setOutlineColor(static_cast<sf::Color>(outline_color));
    sf_polygon.setOutlineThickness(outline_thickness);
    sf_polygon.setFillColor(static_cast<sf::Color>(fill_color));

    _render_target.draw(sf_polygon);
}

void SfmlPrimitiveRenderer::draw_filled_polygon(std::span<const Line> lines, const Color& outline_color,
                                                const Color& fill_color, float outline_thickness) const
{
    sf::ConvexShape sf_polygon;
    sf_polygon.setPointCount(lines.size());

    for (usize i = 0; i < lines.size(); i++)
        sf_polygon.setPoint(i, static_cast<sf::Vector2f>(lines[i].from));

    sf_polygon.setOutlineColor(static_cast<sf::Color>(outline_color));
    sf_polygon.setOutlineThickness(outline_thickness);
    sf_polygon.setFillColor(static_cast<sf::Color>(fill_color));

    _render_target.draw(sf_polygon);
}

void SfmlPrimitiveRenderer::draw_circle(const Circle& circle, const Color& color) const
{
    draw_filled_circle(circle, color, Color::transparent, 1.0f);
}

void SfmlPrimitiveRenderer::draw_ellipse(const Ellipse& ellipse, const Color& color) const
{
    draw_filled_ellipse(ellipse, color, Color::transparent, 1.0f);
}

void SfmlPrimitiveRenderer::draw_filled_circle(const Circle& circle, const Color& outline_color,
                                               const Color& fill_color, float outline_thickness) const
{
    sf::CircleShape sf_circle;
    sf_circle.setRadius(circle.radius);
    sf_circle.setOutlineColor(static_cast<sf::Color>(outline_color));
    sf_circle.setOutlineThickness(outline_thickness);
    sf_circle.setFillColor(static_cast<sf::Color>(fill_color));
    sf_circle.setPosition(static_cast<sf::Vector2f>(circle.center - Vec2f{ circle.radius, circle.radius }));

    _render_target.draw(sf_circle);
}

void SfmlPrimitiveRenderer::draw_filled_ellipse(const Ellipse& ellipse, const Color& outline_color,
                                                const Color& fill_color, float outline_thickness) const
{
    EllipseShape sf_ellipse(ellipse);
    sf_ellipse.setOutlineColor(static_cast<sf::Color>(outline_color));
    sf_ellipse.setOutlineThickness(outline_thickness);
    sf_ellipse.setFillColor(static_cast<sf::Color>(fill_color));

    _render_target.draw(sf_ellipse);
}

void SfmlPrimitiveRenderer::plot_point(const Vec2f& point, const Color& color)
{
    _draw_call.vertices.emplace_back(static_cast<sf::Vector2f>(point), static_cast<sf::Color>(color));
}

void SfmlPrimitiveRenderer::plot_points(std::span<const Vec2f> points, const Color& color)
{
    for (const auto& point : points)
        plot_point(point, color);
}

void SfmlPrimitiveRenderer::plot_line(const Vec2f& from, const Vec2f& to, const Color& color)
{
    _draw_call.vertices.emplace_back(static_cast<sf::Vector2f>(from), static_cast<sf::Color>(color));
    _draw_call.vertices.emplace_back(static_cast<sf::Vector2f>(to), static_cast<sf::Color>(color));
}

void SfmlPrimitiveRenderer::plot_line(const Line& line, const Color& color)
{
    plot_line(line.from, line.to, color);
}

void SfmlPrimitiveRenderer::plot_line_strip(std::span<const Vec2f> points, const Color& color)
{
    plot_points(points, color);
}

void SfmlPrimitiveRenderer::plot_lines(std::span<const Line> lines, const Color& color)
{
    for (const auto& line : lines)
        plot_line(line, color);
}

void SfmlPrimitiveRenderer::plot_closed_lines(std::span<const Vec2f> points, const Color& color)
{
    plot_line_strip(points, color);
    plot_point(points[0], color);
}

void SfmlPrimitiveRenderer::plot_closed_lines(std::span<const Line> lines, const Color& color)
{
    plot_lines(lines, color);

    if (lines.size() < 2)
        return;

    plot_line(lines.back().to, lines.front().from, color);
}

void SfmlPrimitiveRenderer::plot_rect(const Rect& rect, const Color& color)
{
    auto points = rect.points();
    plot_line_strip(points, color);
    plot_point(points[0], color);
}

void SfmlPrimitiveRenderer::plot_polygon(std::span<const Vec2f> points, const Color& color)
{
    plot_line_strip(points, color);
    plot_point(points[0], color);
}

void SfmlPrimitiveRenderer::plot_polygon(std::span<const Line> lines, const Color& color)
{
    plot_lines(lines, color);
}

} // namespace zth
