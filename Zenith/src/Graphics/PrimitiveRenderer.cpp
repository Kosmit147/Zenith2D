#include "Zenith/Graphics/PrimitiveRenderer.hpp"

#include "Zenith/Core/Typedefs.hpp"

namespace zth {

PrimitiveRenderer::PrimitiveRenderer(sf::RenderTarget& target)
    : _render_target(target), _sfml_renderer(target), _custom_renderer(target)
{}

void PrimitiveRenderer::draw_point(const Vec2f& point, const Color& color)
{
    switch (_rendering_algorithm)
    {
    case RenderingAlgorithm::Sfml:
        _sfml_renderer.draw_point(point, color);
        break;
    case RenderingAlgorithm::Custom:
        _custom_renderer.draw_point(point, color);
        break;
    }
}

void PrimitiveRenderer::draw_points(std::span<const Vec2f> points, const Color& color)
{
    if (points.empty())
        return;

    switch (_rendering_algorithm)
    {
    case RenderingAlgorithm::Sfml:
        _sfml_renderer.draw_points(points, color);
        break;
    case RenderingAlgorithm::Custom:
        _custom_renderer.draw_points(points, color);
        break;
    }
}

void PrimitiveRenderer::draw_line(const Vec2f& from, const Vec2f& to, const Color& color)
{
    switch (_rendering_algorithm)
    {
    case RenderingAlgorithm::Sfml:
        _sfml_renderer.draw_line(from, to, color);
        break;
    case RenderingAlgorithm::Custom:
        _custom_renderer.draw_line(from, to, color);
        break;
    }
}

void PrimitiveRenderer::draw_line(const Line& line, const Color& color)
{
    switch (_rendering_algorithm)
    {
    case RenderingAlgorithm::Sfml:
        _sfml_renderer.draw_line(line, color);
        break;
    case RenderingAlgorithm::Custom:
        _custom_renderer.draw_line(line, color);
        break;
    }
}

void PrimitiveRenderer::draw_line_strip(std::span<const Vec2f> points, const Color& color)
{
    if (points.empty())
        return;

    switch (_rendering_algorithm)
    {
    case RenderingAlgorithm::Sfml:
        _sfml_renderer.draw_line_strip(points, color);
        break;
    case RenderingAlgorithm::Custom:
        _custom_renderer.draw_line_strip(points, color);
        break;
    }
}

void PrimitiveRenderer::draw_lines(std::span<const Line> lines, const Color& color)
{
    if (lines.empty())
        return;

    switch (_rendering_algorithm)
    {
    case RenderingAlgorithm::Sfml:
        _sfml_renderer.draw_lines(lines, color);
        break;
    case RenderingAlgorithm::Custom:
        _custom_renderer.draw_lines(lines, color);
        break;
    }
}

void PrimitiveRenderer::draw_closed_lines(std::span<const Vec2f> points, const Color& color)
{
    if (points.empty())
        return;

    switch (_rendering_algorithm)
    {
    case RenderingAlgorithm::Sfml:
        _sfml_renderer.draw_closed_lines(points, color);
        break;
    case RenderingAlgorithm::Custom:
        _custom_renderer.draw_closed_lines(points, color);
        break;
    }
}

void PrimitiveRenderer::draw_closed_lines(std::span<const Line> lines, const Color& color)
{
    if (lines.empty())
        return;

    switch (_rendering_algorithm)
    {
    case RenderingAlgorithm::Sfml:
        _sfml_renderer.draw_closed_lines(lines, color);
        break;
    case RenderingAlgorithm::Custom:
        _custom_renderer.draw_closed_lines(lines, color);
        break;
    }
}

void PrimitiveRenderer::draw_rect(const Rect& rect, const Color& color)
{
    switch (_rendering_algorithm)
    {
    case RenderingAlgorithm::Sfml:
        _sfml_renderer.draw_rect(rect, color);
        break;
    case RenderingAlgorithm::Custom:
        _custom_renderer.draw_rect(rect, color);
        break;
    }
}

void PrimitiveRenderer::draw_filled_rect(const Rect& rect, const Color& color)
{
    switch (_rendering_algorithm)
    {
    case RenderingAlgorithm::Sfml:
        _sfml_renderer.draw_filled_rect(rect, color);
        break;
    case RenderingAlgorithm::Custom:
        _custom_renderer.draw_filled_rect(rect, color);
        break;
    }
}

static bool points_form_a_valid_polygon(std::span<const Vec2f> points)
{
    if (points.empty())
        return false;

    // check if any lines intersect each other
    for (usize i = 0; i < points.size() - 1; i++)
    {
        Line current_line = { points[i], points[i + 1] };

        for (usize j = i + 1; j < points.size() - 1; j++)
        {
            Line other_line = { points[j], points[j + 1] };

            if (current_line.intersects(other_line))
                return false;
        }

        Line closing_line = { points[points.size() - 1], points[0] };

        if (current_line.intersects(closing_line))
            return false;
    }

    return true;
}

static bool lines_form_a_valid_polygon(std::span<const Line> lines)
{
    if (lines.empty())
        return false;

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

void PrimitiveRenderer::draw_polygon(std::span<const Vec2f> points, const Color& color)
{
    if (points.size() < 2)
        return;

    if (!points_form_a_valid_polygon(points))
        return;

    switch (_rendering_algorithm)
    {
    case RenderingAlgorithm::Sfml:
        _sfml_renderer.draw_polygon(points, color);
        break;
    case RenderingAlgorithm::Custom:
        _custom_renderer.draw_polygon(points, color);
        break;
    }
}

void PrimitiveRenderer::draw_polygon(std::span<const Line> lines, const Color& color)
{
    if (lines.empty())
        return;

    if (!lines_form_a_valid_polygon(lines))
        return;

    switch (_rendering_algorithm)
    {
    case RenderingAlgorithm::Sfml:
        _sfml_renderer.draw_polygon(lines, color);
        break;
    case RenderingAlgorithm::Custom:
        _custom_renderer.draw_polygon(lines, color);
        break;
    }
}

void PrimitiveRenderer::draw_filled_polygon(std::span<const Vec2f> points, const Color& color)
{
    if (points.size() < 2)
        return;

    if (!points_form_a_valid_polygon(points))
        return;

    switch (_rendering_algorithm)
    {
    case RenderingAlgorithm::Sfml:
        _sfml_renderer.draw_filled_polygon(points, color);
        break;
    case RenderingAlgorithm::Custom:
        _custom_renderer.draw_filled_polygon(points, color);
        break;
    }
}

void PrimitiveRenderer::draw_filled_polygon(std::span<const Line> lines, const Color& color)
{
    if (lines.empty())
        return;

    if (!lines_form_a_valid_polygon(lines))
        return;

    switch (_rendering_algorithm)
    {
    case RenderingAlgorithm::Sfml:
        _sfml_renderer.draw_filled_polygon(lines, color);
        break;
    case RenderingAlgorithm::Custom:
        _custom_renderer.draw_filled_polygon(lines, color);
        break;
    }
}

void PrimitiveRenderer::draw_circle(const Circle& circle, const Color& color)
{
    switch (_rendering_algorithm)
    {
    case RenderingAlgorithm::Sfml:
        _sfml_renderer.draw_circle(circle, color);
        break;
    case RenderingAlgorithm::Custom:
        _custom_renderer.draw_circle(circle, color);
        break;
    }
}

void PrimitiveRenderer::draw_filled_circle(const Circle& circle, const Color& color) const
{
    switch (_rendering_algorithm)
    {
    case RenderingAlgorithm::Sfml:
        _sfml_renderer.draw_filled_circle(circle, color);
        break;
    case RenderingAlgorithm::Custom:
        _custom_renderer.draw_filled_circle(circle, color);
        break;
    }
}

void PrimitiveRenderer::draw_ellipse(const Ellipse& ellipse, const Color& color)
{
    switch (_rendering_algorithm)
    {
    case RenderingAlgorithm::Sfml:
        _sfml_renderer.draw_ellipse(ellipse, color);
        break;
    case RenderingAlgorithm::Custom:
        _custom_renderer.draw_ellipse(ellipse, color);
        break;
    }
}

void PrimitiveRenderer::draw_filled_ellipse(const Ellipse& ellipse, const Color& color) const
{
    switch (_rendering_algorithm)
    {
    case RenderingAlgorithm::Sfml:
        _sfml_renderer.draw_filled_ellipse(ellipse, color);
        break;
    case RenderingAlgorithm::Custom:
        _custom_renderer.draw_filled_ellipse(ellipse, color);
        break;
    }
}

} // namespace zth
