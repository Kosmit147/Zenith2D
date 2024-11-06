#pragma once

#include <SFML/Graphics.hpp>

#include <span>

#include "Zenith/Graphics/Color.hpp"
#include "Zenith/Math/Geometry.hpp"
#include "Zenith/Math/Vec2.hpp"
#include "Zenith/Utility/Utility.hpp"

namespace zth {

// PrimitiveRenderer should check whether the data provided to it is correct
class PrimitiveRenderer
{
public:
    explicit PrimitiveRenderer(sf::RenderTarget& render_target) : _render_target(render_target) {}
    virtual ~PrimitiveRenderer() = default;
    ZTH_NO_COPY_NO_MOVE(PrimitiveRenderer)

    void draw_point(const Vec2f& point, const Color& color);
    void draw_points(std::span<const Vec2f> points, const Color& color);
    void draw_line(const Vec2f& from, const Vec2f& to, const Color& color);
    void draw_line(const Line& line, const Color& color);
    void draw_line_strip(std::span<const Vec2f> points, const Color& color);
    void draw_lines(std::span<const Line> lines, const Color& color);
    void draw_closed_lines(std::span<const Vec2f> points, const Color& color);
    void draw_closed_lines(std::span<const Line> lines, const Color& color);

    void draw_rect(const Rect& rect, const Color& color);
    void draw_filled_rect(const Rect& rect, const Color& color);

    void draw_convex_polygon(std::span<const Vec2f> points, const Color& color);
    void draw_convex_polygon(std::span<const Line> lines, const Color& color);
    void draw_filled_convex_polygon(std::span<const Vec2f> points, const Color& color);
    void draw_filled_convex_polygon(std::span<const Line> lines, const Color& color);

    void draw_circle(const Circle& circle, const Color& color);
    void draw_ellipse(const Ellipse& ellipse, const Color& color);
    void draw_filled_circle(const Circle& circle, const Color& color);
    void draw_filled_ellipse(const Ellipse& ellipse, const Color& color);

protected:
    sf::RenderTarget& _render_target;

private:
    virtual void draw_point_impl(const Vec2f& point, const Color& color) = 0;
    virtual void draw_points_impl(std::span<const Vec2f> points, const Color& color) = 0;
    virtual void draw_line_impl(const Vec2f& from, const Vec2f& to, const Color& color) = 0;
    virtual void draw_line_impl(const Line& line, const Color& color) = 0;
    virtual void draw_line_strip_impl(std::span<const Vec2f> points, const Color& color) = 0;
    virtual void draw_lines_impl(std::span<const Line> lines, const Color& color) = 0;
    virtual void draw_closed_lines_impl(std::span<const Vec2f> points, const Color& color) = 0;
    virtual void draw_closed_lines_impl(std::span<const Line> lines, const Color& color) = 0;

    virtual void draw_rect_impl(const Rect& rect, const Color& color) = 0;
    virtual void draw_filled_rect_impl(const Rect& rect, const Color& color) = 0;

    virtual void draw_convex_polygon_impl(std::span<const Vec2f> points, const Color& color) = 0;
    virtual void draw_convex_polygon_impl(std::span<const Line> lines, const Color& color) = 0;
    virtual void draw_filled_convex_polygon_impl(std::span<const Vec2f> points, const Color& color) = 0;
    virtual void draw_filled_convex_polygon_impl(std::span<const Line> lines, const Color& color) = 0;

    virtual void draw_circle_impl(const Circle& circle, const Color& color) = 0;
    virtual void draw_ellipse_impl(const Ellipse& ellipse, const Color& color) = 0;
    virtual void draw_filled_circle_impl(const Circle& circle, const Color& color) = 0;
    virtual void draw_filled_ellipse_impl(const Ellipse& ellipse, const Color& color) = 0;
};

} // namespace zth
