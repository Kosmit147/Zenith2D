#include "SfmlPrimitiveRenderer.hpp"

#include "EllipseShape.hpp"

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

void SfmlPrimitiveRenderer::draw_filled_rect(const Rect& rect, const Color& color)
{
    plot_filled_rect(rect, color);
    _draw_call.execute(_render_target, sf::TriangleStrip);
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

void SfmlPrimitiveRenderer::draw_filled_polygon(std::span<const Vec2f> points, const Color& color)
{
    plot_filled_polygon(points, color);
    _draw_call.execute(_render_target, sf::TriangleFan);
}

void SfmlPrimitiveRenderer::draw_filled_polygon(std::span<const Line> lines, const Color& color)
{
    plot_filled_polygon(lines, color);
    _draw_call.execute(_render_target, sf::TriangleFan);
}

void SfmlPrimitiveRenderer::draw_circle(const Circle& circle, const Color& color) const
{
    // TODO: handle this on our own instead of using SFML shapes
    sf::CircleShape sf_circle;
    sf_circle.setRadius(circle.radius);
    sf_circle.setOutlineColor(static_cast<sf::Color>(color));
    sf_circle.setOutlineThickness(1);
    sf_circle.setFillColor(static_cast<sf::Color>(Color::transparent));
    sf_circle.setPosition(static_cast<sf::Vector2f>(circle.center - Vec2f{ circle.radius, circle.radius }));

    _render_target.draw(sf_circle);
}

void SfmlPrimitiveRenderer::draw_ellipse(const Ellipse& ellipse, const Color& color) const
{
    // TODO: handle this on our own instead of using SFML shapes
    EllipseShape sf_ellipse(ellipse);
    sf_ellipse.setOutlineColor(static_cast<sf::Color>(color));
    sf_ellipse.setOutlineThickness(1);
    sf_ellipse.setFillColor(static_cast<sf::Color>(Color::transparent));

    _render_target.draw(sf_ellipse);
}

void SfmlPrimitiveRenderer::draw_filled_circle(const Circle& circle, const Color& color) const
{
    // TODO: handle this on our own instead of using SFML shapes
    sf::CircleShape sf_circle;
    sf_circle.setRadius(circle.radius);
    sf_circle.setOutlineColor(static_cast<sf::Color>(color));
    sf_circle.setOutlineThickness(1);
    sf_circle.setFillColor(static_cast<sf::Color>(color));
    sf_circle.setPosition(static_cast<sf::Vector2f>(circle.center - Vec2f{ circle.radius, circle.radius }));

    _render_target.draw(sf_circle);
}

void SfmlPrimitiveRenderer::draw_filled_ellipse(const Ellipse& ellipse, const Color& color) const
{
    // TODO: handle this on our own instead of using SFML shapes
    EllipseShape sf_ellipse(ellipse);
    sf_ellipse.setOutlineColor(static_cast<sf::Color>(color));
    sf_ellipse.setOutlineThickness(1);
    sf_ellipse.setFillColor(static_cast<sf::Color>(color));

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

void SfmlPrimitiveRenderer::plot_filled_rect(const Rect& rect, const Color& color)
{
    auto points = rect.points();

    // have to plot the corner first, then the diagonal

    plot_point(points[1], color);
    plot_point(points[0], color);
    plot_point(points[2], color);
    plot_point(points[3], color);
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

void SfmlPrimitiveRenderer::plot_filled_polygon(std::span<const Vec2f> points, const Color& color)
{
    auto center_point = std::reduce(points.begin(), points.end()) / static_cast<float>(points.size());
    plot_point(center_point, color);
    plot_line_strip(points, color);
    plot_point(points[0], color);
}

void SfmlPrimitiveRenderer::plot_filled_polygon(std::span<const Line> lines, const Color& color)
{
    auto points_sum = std::transform_reduce(lines.begin(), lines.end(), Vec2f{ 0.0f, 0.0f }, std::plus{},
                                            [](auto& line) { return line.from; });
    auto center_point = points_sum / static_cast<float>(lines.size());
    plot_point(center_point, color);

    for (const auto& [from, to] : lines)
        plot_point(from, color);

    plot_point(lines.back().to, color);
}

} // namespace zth
