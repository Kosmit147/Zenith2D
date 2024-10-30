#pragma once

#include <SFML/Graphics.hpp>

#include <span>

#include "Color.hpp"
#include "DrawCall.hpp"
#include "Geometry.hpp"

namespace zth {

class SfmlRenderer
{
public:
    explicit SfmlRenderer(sf::RenderTarget& target) : _target(target) {}

    SfmlRenderer(const SfmlRenderer&) = delete;
    SfmlRenderer(SfmlRenderer&&) = delete;

    ~SfmlRenderer() = default;

    auto operator=(const SfmlRenderer&) = delete;
    auto operator=(SfmlRenderer&&) = delete;

    void draw_line(const Vec2f& from, const Vec2f& to, const Color& color);
    void draw_line(const Line& line, const Color& color);

    void draw_rect(const Rect& rect, const Color& outline_color);
    void draw_filled_rect(const Rect& rect, const Color& outline_color, const Color& fill_color = Color::transparent);

    void draw_polygon(std::span<const Vec2f> points, const Color& outline_color);
    void draw_polygon(std::span<const Line> lines, const Color& outline_color);
    void draw_filled_polygon(std::span<const Vec2f> points, const Color& outline_color,
                             const Color& fill_color = Color::transparent);
    void draw_filled_polygon(std::span<const Line> lines, const Color& outline_color,
                             const Color& fill_color = Color::transparent);

    void draw_circle(const Circle& circle, const Color& outline_color, const Color& fill_color = Color::transparent);
    void draw_ellipse(const Ellipse& ellipse, const Color& outline_color, const Color& fill_color = Color::transparent);

private:
    sf::RenderTarget& _target;
    DrawCall _draw_call = DrawCall{};

private:
    void plot_line(const Vec2f& from, const Vec2f& to, const Color& color);
    void plot_line(const Line& line, const Color& color);

    void plot_rect(const Rect& rect, const Color& outline_color, const Color& fill_color);
};

} // namespace zth
