#pragma once

#include <SFML/Graphics.hpp>

#include <span>

#include "Color.hpp"
#include "Geometry.hpp"

namespace zth {

class Window;

enum class RenderingAlgorithm
{
    Sfml,
    Custom,
};

class PrimitiveRenderer
{
public:
    RenderingAlgorithm rendering_algorithm = RenderingAlgorithm::Sfml;

public:
    explicit PrimitiveRenderer(sf::RenderWindow& window) : _window(window) {}

    PrimitiveRenderer(const PrimitiveRenderer&) = delete;
    PrimitiveRenderer(PrimitiveRenderer&&) = delete;

    ~PrimitiveRenderer() = default;

    PrimitiveRenderer& operator=(const PrimitiveRenderer&) = delete;
    PrimitiveRenderer& operator=(PrimitiveRenderer&&) = delete;

    void draw_point(Point2D point, const Color& color = Color::white) const;

    void draw_line(const Point2D& from, const Point2D& to, const Color& color = Color::white) const;

    void draw_line(const Line& line, const Color& color = Color::white) const;

    void draw_lines(std::span<const Point2D> points, const Color& color = Color::white) const;

    void draw_lines(std::span<const Line> lines, const Color& color = Color::white) const;

    void draw_closed_lines(std::span<const Point2D> points, const Color& color = Color::white) const;

    void draw_closed_lines(std::span<const Line> lines, const Color& color = Color::white) const;

    void draw_rect(const Rect& rect, const Color& color = Color::white) const;

    void draw_filled_rect(const Rect& rect, const Color& outline_color = Color::white,
                          const Color& fill_color = Color::black) const;

    void draw_polygon(std::span<const Point2D> points, const Color& color = Color::white) const;

    void draw_polygon(std::span<const Line> lines, const Color& color = Color::white) const;

    void draw_filled_polygon(std::span<const Point2D> points, const Color& outline_color = Color::white,
                             const Color& fill_color = Color::black) const;

    void draw_filled_polygon(std::span<const Line> lines, const Color& outline_color = Color::white,
                             const Color& fill_color = Color::black) const;

    void draw_circle(const Circle& circle, const Color& color = Color::white) const;

    void draw_filled_circle(const Circle& circle, const Color& outline_color = Color::white,
                            const Color& fill_color = Color::black) const;

    void draw_ellipse(const Ellipse& ellipse, const Color& color = Color::white) const;

    void draw_filled_ellipse(const Ellipse& ellipse, const Color& outline_color = Color::white,
                             const Color& fill_color = Color::black) const;

private:
    sf::RenderWindow& _window;

private:
    void draw_line_sfml(const Point2D& from, const Point2D& to, const Color& color) const;

    void draw_line_sfml(const Line& line, const Color& color) const;

    void draw_line_custom(const Point2D& from, const Point2D& to, const Color& color) const;

    void draw_line_custom(const Line& line, const Color& color) const;

    void draw_rect_sfml(const Rect& rect, const Color& outline_color,
                        const Color& fill_color = Color::transparent) const;

    void draw_polygon_sfml(std::span<const Point2D> points, const Color& outline_color,
                           const Color& fill_color = Color::transparent) const;

    void draw_polygon_sfml(std::span<const Line> lines, const Color& outline_color,
                           const Color& fill_color = Color::transparent) const;

    void draw_polygon_custom(std::span<const Point2D> points, const Color& outline_color) const;

    void draw_polygon_custom(std::span<const Line> lines, const Color& outline_color) const;

    void draw_circle_sfml(const Circle& circle, const Color& outline_color,
                          const Color& fill_color = Color::transparent) const;

    void draw_circle_custom(const Circle& circle, const Color& color) const;

    void draw_ellipse_sfml(const Ellipse& ellipse, const Color& outline_color,
                           const Color& fill_color = Color::transparent) const;

    void draw_ellipse_custom(const Ellipse& ellipse, const Color& color) const;
};

} // namespace zth
