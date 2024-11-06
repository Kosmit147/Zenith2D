#include "Zenith/Graphics/PrimitiveRenderer.hpp"

#include "Zenith/Core/Typedefs.hpp"

namespace zth {

void PrimitiveRenderer::draw_point(const Vec2f& point, const Color& color)
{
    draw_point_impl(point, color);
}

void PrimitiveRenderer::draw_points(std::span<const Vec2f> points, const Color& color)
{
    if (points.empty())
        return;

    draw_points_impl(points, color);
}

void PrimitiveRenderer::draw_line(const Vec2f& from, const Vec2f& to, const Color& color)
{
    draw_line_impl(from, to, color);
}

void PrimitiveRenderer::draw_line(const Line& line, const Color& color)
{
    draw_line_impl(line, color);
}

void PrimitiveRenderer::draw_line_strip(std::span<const Vec2f> points, const Color& color)
{
    if (points.empty())
        return;

    draw_line_strip_impl(points, color);
}

void PrimitiveRenderer::draw_lines(std::span<const Line> lines, const Color& color)
{
    if (lines.empty())
        return;

    draw_lines_impl(lines, color);
}

void PrimitiveRenderer::draw_closed_lines(std::span<const Vec2f> points, const Color& color)
{
    if (points.empty())
        return;

    draw_closed_lines_impl(points, color);
}

void PrimitiveRenderer::draw_closed_lines(std::span<const Line> lines, const Color& color)
{
    if (lines.empty())
        return;

    draw_closed_lines_impl(lines, color);
}

void PrimitiveRenderer::draw_rect(const Rect& rect, const Color& color)
{
    draw_rect_impl(rect, color);
}

void PrimitiveRenderer::draw_filled_rect(const Rect& rect, const Color& color)
{
    draw_filled_rect_impl(rect, color);
}

void PrimitiveRenderer::draw_convex_polygon(std::span<const Vec2f> points, const Color& color)
{
    if (points.size() < 2)
        return;

    if (!points_form_a_valid_polygon(points))
        return;

    draw_convex_polygon_impl(points, color);
}

void PrimitiveRenderer::draw_convex_polygon(std::span<const Line> lines, const Color& color)
{
    if (lines.empty())
        return;

    if (!lines_form_a_valid_polygon(lines))
        return;

    draw_convex_polygon_impl(lines, color);
}

void PrimitiveRenderer::draw_filled_convex_polygon(std::span<const Vec2f> points, const Color& color)
{
    if (points.size() < 2)
        return;

    if (!points_form_a_valid_polygon(points))
        return;

    draw_filled_convex_polygon_impl(points, color);
}

void PrimitiveRenderer::draw_filled_convex_polygon(std::span<const Line> lines, const Color& color)
{
    if (lines.empty())
        return;

    if (!lines_form_a_valid_polygon(lines))
        return;

    draw_filled_convex_polygon_impl(lines, color);
}

void PrimitiveRenderer::draw_circle(const Circle& circle, const Color& color)
{
    draw_circle_impl(circle, color);
}

void PrimitiveRenderer::draw_ellipse(const Ellipse& ellipse, const Color& color)
{
    draw_ellipse_impl(ellipse, color);
}

void PrimitiveRenderer::draw_filled_circle(const Circle& circle, const Color& color)
{
    draw_filled_circle_impl(circle, color);
}

void PrimitiveRenderer::draw_filled_ellipse(const Ellipse& ellipse, const Color& color)
{
    draw_filled_ellipse_impl(ellipse, color);
}

} // namespace zth
