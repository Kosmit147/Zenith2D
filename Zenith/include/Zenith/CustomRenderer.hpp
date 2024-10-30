#pragma once

#include <SFML/Graphics.hpp>

#include <span>

#include "Color.hpp"
#include "DrawCall.hpp"
#include "Geometry.hpp"

namespace zth {

class CustomRenderer
{
public:
    explicit CustomRenderer(sf::RenderTarget& target) : _target(target) {}

    CustomRenderer(const CustomRenderer&) = delete;
    CustomRenderer(CustomRenderer&&) = delete;

    ~CustomRenderer() = default;

    auto operator=(const CustomRenderer&) = delete;
    auto operator=(CustomRenderer&&) = delete;

    void draw_line(const Vec2f& from, const Vec2f& to, const Color& color);
    void draw_line(const Line& line, const Color& color);

    void draw_rect(const Rect& rect, const Color& outline_color);
    void draw_filled_rect(const Rect& rect, const Color& outline_color);

    void draw_polygon(std::span<const Vec2f> points, const Color& outline_color);
    void draw_polygon(std::span<const Line> lines, const Color& outline_color);

    void draw_filled_polygon(std::span<const Vec2f> points, const Color& outline_color, const Color& fill_color);
    void draw_filled_polygon(std::span<const Line> lines, const Color& outline_color, const Color& fill_color);

    void draw_circle(const Circle& circle, const Color& color);
    void draw_ellipse(const Ellipse& ellipse, const Color& color);

    static void draw_line_on_image(sf::Image& image, const Vec2f& from, const Vec2f& to, const Color& color);
    static void draw_line_on_image(sf::Image& image, const Line& line, const Color& color);
    static void draw_lines_on_image(sf::Image& image, std::span<const Vec2f> points, const Color& color);
    static void draw_lines_on_image(sf::Image& image, std::span<const Line> lines, const Color& color);

    static void boundary_fill(sf::Image& image, const Vec2f& seed, const Color& border_color, const Color& fill_color);
    static void flood_fill(sf::Image& image, const Vec2f& seed, const Color& fill_color, const Color& background_color);

    sf::Image& get_tmp_image(sf::Vector2u size);

private:
    sf::RenderTarget& _target;
    DrawCall _draw_call = DrawCall{};
};

} // namespace zth
