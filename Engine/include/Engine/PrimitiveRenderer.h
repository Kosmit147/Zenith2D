#pragma once

#include <SFML/Graphics.hpp>

#include <span>

#include "Color.h"
#include "Geometry.h"

class Window;

enum class RenderingAlgorithm
{
    SFML,
    Custom,
};

class PrimitiveRenderer
{
public:
    inline PrimitiveRenderer(Window* window) : _window(window) {}

    void draw(Point2D point, const Color& color = Color::White);
    void draw(const Line& line, const Color& color = Color::White,
              RenderingAlgorithm alg = RenderingAlgorithm::SFML);
    void draw(std::span<Line> lines, const Color& color = Color::White,
              RenderingAlgorithm alg = RenderingAlgorithm::SFML);
    void draw(const Circle& circle, const Color& color = Color::White,
              RenderingAlgorithm alg = RenderingAlgorithm::SFML);
    void draw(const Ellipse& ellipse, const Color& color = Color::White,
              RenderingAlgorithm alg = RenderingAlgorithm::SFML);

private:
    Window* _window;

private:
    void draw_line_sfml(const Line& line, const Color& color);
    void draw_line_custom(const Line& line, const Color& color);
};
