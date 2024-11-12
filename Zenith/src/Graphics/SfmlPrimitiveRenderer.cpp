#include "Zenith/Graphics/SfmlPrimitiveRenderer.hpp"

#include <SFML/Graphics/CircleShape.hpp>

#include "Zenith/Graphics/SfmlEllipseShape.hpp"

namespace zth {

void SfmlPrimitiveRenderer::draw_point_impl(const Vec2f& point, const Color& color)
{
    plot_point(point, color);
    draw_call(PrimitiveType::Points);
}

void SfmlPrimitiveRenderer::draw_points_impl(std::span<const Vec2f> points, const Color& color)
{
    plot_points(points, color);
    draw_call(PrimitiveType::Points);
}

void SfmlPrimitiveRenderer::draw_line_impl(const Vec2f& from, const Vec2f& to, const Color& color)
{
    plot_line(from, to, color);
    draw_call(PrimitiveType::Lines);
}

void SfmlPrimitiveRenderer::draw_line_impl(const Line& line, const Color& color)
{
    plot_line(line, color);
    draw_call(PrimitiveType::Lines);
}

void SfmlPrimitiveRenderer::draw_line_strip_impl(std::span<const Vec2f> points, const Color& color)
{
    plot_line_strip(points, color);
    draw_call(PrimitiveType::LineStrip);
}

void SfmlPrimitiveRenderer::draw_lines_impl(std::span<const Line> lines, const Color& color)
{
    plot_lines(lines, color);
    draw_call(PrimitiveType::Lines);
}

void SfmlPrimitiveRenderer::draw_closed_lines_impl(std::span<const Vec2f> points, const Color& color)
{
    plot_closed_lines(points, color);
    draw_call(PrimitiveType::LineStrip);
}

void SfmlPrimitiveRenderer::draw_closed_lines_impl(std::span<const Line> lines, const Color& color)
{
    plot_closed_lines(lines, color);
    draw_call(PrimitiveType::Lines);
}

void SfmlPrimitiveRenderer::draw_triangle_impl(const Triangle& triangle, const Color& color)
{
    plot_triangle(triangle, color);
    draw_call(PrimitiveType::LineStrip);
}

void SfmlPrimitiveRenderer::draw_filled_triangle_impl(const Triangle& triangle, const Color& color)
{
    plot_filled_triangle(triangle, color);
    draw_call(PrimitiveType::Triangles);
}

void SfmlPrimitiveRenderer::draw_rect_impl(const Rect& rect, const Color& color)
{
    plot_rect(rect, color);
    draw_call(PrimitiveType::LineStrip);
}

void SfmlPrimitiveRenderer::draw_filled_rect_impl(const Rect& rect, const Color& color)
{
    plot_filled_rect(rect, color);
    draw_call(PrimitiveType::TriangleStrip);
}

void SfmlPrimitiveRenderer::draw_convex_polygon_impl(std::span<const Vec2f> points, const Color& color)
{
    plot_convex_polygon(points, color);
    draw_call(PrimitiveType::LineStrip);
}

void SfmlPrimitiveRenderer::draw_convex_polygon_impl(std::span<const Line> lines, const Color& color)
{
    plot_convex_polygon(lines, color);
    draw_call(PrimitiveType::Lines);
}

void SfmlPrimitiveRenderer::draw_filled_convex_polygon_impl(std::span<const Vec2f> points, const Color& color)
{
    plot_filled_convex_polygon(points, color);
    draw_call(PrimitiveType::TriangleFan);
}

void SfmlPrimitiveRenderer::draw_filled_convex_polygon_impl(std::span<const Line> lines, const Color& color)
{
    plot_filled_convex_polygon(lines, color);
    draw_call(PrimitiveType::TriangleFan);
}

void SfmlPrimitiveRenderer::draw_circle_impl(const Circle& circle, const Color& color)
{
    sf::CircleShape sf_circle;
    sf_circle.setRadius(circle.radius);
    sf_circle.setOutlineColor(static_cast<sf::Color>(color));
    sf_circle.setOutlineThickness(1);
    sf_circle.setFillColor(static_cast<sf::Color>(Color::transparent));
    sf_circle.setPosition(static_cast<sf::Vector2f>(circle.center - Vec2f{ circle.radius, circle.radius }));

    _render_target.draw(sf_circle);
}

void SfmlPrimitiveRenderer::draw_ellipse_impl(const Ellipse& ellipse, const Color& color)
{
    SfmlEllipseShape sf_ellipse(ellipse);
    sf_ellipse.setOutlineColor(static_cast<sf::Color>(color));
    sf_ellipse.setOutlineThickness(1);
    sf_ellipse.setFillColor(static_cast<sf::Color>(Color::transparent));

    _render_target.draw(sf_ellipse);
}

void SfmlPrimitiveRenderer::draw_filled_circle_impl(const Circle& circle, const Color& color)
{
    sf::CircleShape sf_circle;
    sf_circle.setRadius(circle.radius);
    sf_circle.setOutlineColor(static_cast<sf::Color>(color));
    sf_circle.setOutlineThickness(1);
    sf_circle.setFillColor(static_cast<sf::Color>(color));
    sf_circle.setPosition(static_cast<sf::Vector2f>(circle.center - Vec2f{ circle.radius, circle.radius }));

    _render_target.draw(sf_circle);
}

void SfmlPrimitiveRenderer::draw_filled_ellipse_impl(const Ellipse& ellipse, const Color& color)
{
    SfmlEllipseShape sf_ellipse(ellipse);
    sf_ellipse.setOutlineColor(static_cast<sf::Color>(color));
    sf_ellipse.setOutlineThickness(1);
    sf_ellipse.setFillColor(static_cast<sf::Color>(color));

    _render_target.draw(sf_ellipse);
}

void SfmlPrimitiveRenderer::plot_point(const Vec2f& point, const Color& color)
{
    _vertex_array.append({ point, color });
}

void SfmlPrimitiveRenderer::plot_points(std::span<const Vec2f> points, const Color& color)
{
    for (const auto& point : points)
        plot_point(point, color);
}

void SfmlPrimitiveRenderer::plot_line(const Vec2f& from, const Vec2f& to, const Color& color)
{
    plot_point(from, color);
    plot_point(to, color);
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

void SfmlPrimitiveRenderer::plot_triangle(const Triangle& triangle, const Color& color)
{
    plot_line_strip(triangle.points, color);
    plot_point(triangle.points[0], color);
}

void SfmlPrimitiveRenderer::plot_filled_triangle(const Triangle& triangle, const Color& color)
{
    plot_points(triangle.points, color);
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

    // have to plot the corner first, then the diagonal because we're drawing a triangle strip
    plot_point(points[1], color);
    plot_point(points[0], color);
    plot_point(points[2], color);
    plot_point(points[3], color);
}

void SfmlPrimitiveRenderer::plot_convex_polygon(std::span<const Vec2f> points, const Color& color)
{
    plot_line_strip(points, color);
    plot_point(points[0], color);
}

void SfmlPrimitiveRenderer::plot_convex_polygon(std::span<const Line> lines, const Color& color)
{
    plot_lines(lines, color);
}

void SfmlPrimitiveRenderer::plot_filled_convex_polygon(std::span<const Vec2f> points, const Color& color)
{
    auto center_point = std::reduce(points.begin(), points.end()) / static_cast<float>(points.size());
    plot_point(center_point, color);
    plot_line_strip(points, color);
    plot_point(points[0], color);
}

void SfmlPrimitiveRenderer::plot_filled_convex_polygon(std::span<const Line> lines, const Color& color)
{
    auto points_sum = std::transform_reduce(lines.begin(), lines.end(), Vec2f{ 0.0f, 0.0f }, std::plus{},
                                            [](auto& line) { return line.from; });
    auto center_point = points_sum / static_cast<float>(lines.size());

    plot_point(center_point, color);

    for (const auto& [from, to] : lines)
        plot_point(from, color);

    plot_point(lines.back().to, color);
}

void SfmlPrimitiveRenderer::draw_call(PrimitiveType primitive_type)
{
    _vertex_array.set_primitive_type(primitive_type);
    _render_target.draw(_vertex_array._vertex_array);
    _vertex_array.clear();
}

} // namespace zth
