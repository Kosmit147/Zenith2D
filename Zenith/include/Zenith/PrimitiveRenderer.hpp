#pragma once

#include <span>

#include "Color.hpp"
#include "Geometry.hpp"

namespace zth {

class Window;

enum class RenderingAlgorithm
{
    SFML,
    Custom,
};

class PrimitiveRenderer
{
public:
    inline PrimitiveRenderer(Window& window) : _window(window) {}

    void draw_point(Point2D point, const Color& color = Color::White);

    void draw_line(const Point2D& from, const Point2D& to, const Color& color = Color::White,
                   RenderingAlgorithm alg = RenderingAlgorithm::SFML);

    void draw_line(const Line& line, const Color& color = Color::White,
                   RenderingAlgorithm alg = RenderingAlgorithm::SFML);

    void draw_lines(std::span<const Point2D> points, const Color& color = Color::White,
                    RenderingAlgorithm alg = RenderingAlgorithm::SFML);

    void draw_lines(std::span<const Line> lines, const Color& color = Color::White,
                    RenderingAlgorithm alg = RenderingAlgorithm::SFML);

    void draw_closed_lines(std::span<const Point2D> points, const Color& color = Color::White,
                           RenderingAlgorithm alg = RenderingAlgorithm::SFML);

    void draw_closed_lines(std::span<const Line> lines, const Color& color = Color::White,
                           RenderingAlgorithm alg = RenderingAlgorithm::SFML);

    void draw_rect(const Rect& rect, const Color& color = Color::White,
                   RenderingAlgorithm alg = RenderingAlgorithm::SFML);

    void draw_filled_rect(const Rect& rect, const Color& outline_color = Color::White,
                          const Color& fill_color = Color::Black, RenderingAlgorithm alg = RenderingAlgorithm::SFML);

    void draw_polygon(std::span<const Point2D> points, const Color& color = Color::White,
                      RenderingAlgorithm alg = RenderingAlgorithm::SFML);

    void draw_polygon(std::span<const Line> lines, const Color& color = Color::White,
                      RenderingAlgorithm alg = RenderingAlgorithm::SFML);

    void draw_filled_polygon(std::span<const Point2D> points, const Color& outline_color = Color::White,
                             const Color& fill_color = Color::Black, RenderingAlgorithm alg = RenderingAlgorithm::SFML);

    void draw_filled_polygon(std::span<const Line> lines, const Color& outline_color = Color::White,
                             const Color& fill_color = Color::Black, RenderingAlgorithm alg = RenderingAlgorithm::SFML);

    void draw_circle(const Circle& circle, const Color& color = Color::White,
                     RenderingAlgorithm alg = RenderingAlgorithm::SFML);

    void draw_filled_circle(const Circle& circle, const Color& outline_color = Color::White,
                            const Color& fill_color = Color::Black, RenderingAlgorithm alg = RenderingAlgorithm::SFML);

    void draw_ellipse(const Ellipse& ellipse, const Color& color = Color::White,
                      RenderingAlgorithm alg = RenderingAlgorithm::SFML);

    void draw_filled_ellipse(const Ellipse& ellipse, const Color& outline_color = Color::White,
                             const Color& fill_color = Color::Black, RenderingAlgorithm alg = RenderingAlgorithm::SFML);

private:
    Window& _window;

private:
    void draw_line_sfml(const Point2D& from, const Point2D& to, const Color& color);

    void draw_line_sfml(const Line& line, const Color& color);

    void draw_line_custom(const Point2D& from, const Point2D& to, const Color& color);

    void draw_line_custom(const Line& line, const Color& color);

    void draw_rect_sfml(const Rect& rect, const Color& outline_color, const Color& fill_color = Color::Transparent);

    void draw_polygon_sfml(std::span<const Point2D> points, const Color& outline_color,
                           const Color& fill_color = Color::Transparent);

    void draw_polygon_sfml(std::span<const Line> lines, const Color& outline_color,
                           const Color& fill_color = Color::Transparent);

    void draw_polygon_custom(std::span<const Point2D> points, const Color& outline_color);

    void draw_polygon_custom(std::span<const Line> lines, const Color& outline_color);

    void draw_circle_sfml(const Circle& circle, const Color& outline_color,
                          const Color& fill_color = Color::Transparent);

    void draw_circle_custom(const Circle& circle, const Color& color);

    void draw_ellipse_sfml(const Ellipse& ellipse, const Color& outline_color,
                           const Color& fill_color = Color::Transparent);

    void draw_ellipse_custom(const Ellipse& ellipse, const Color& color);
};

} // namespace zth
