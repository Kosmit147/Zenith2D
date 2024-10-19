#pragma once

#include <SFML/Graphics.hpp>

#include <span>

#include "Color.h"
#include "Geometry.h"

class Window;

enum class LineRenderingAlgorithm
{
    Default,
    Incremental,
};

class PrimitiveRenderer
{
public:
    inline PrimitiveRenderer(Window* window) : _window(window) {}

    void draw(Point2D point, const Color& color = Color::White);
    void draw(const Line& line, const Color& color = Color::White,
              LineRenderingAlgorithm alg = LineRenderingAlgorithm::Default);
    void draw(std::span<Line> lines, const Color& color = Color::White,
              LineRenderingAlgorithm alg = LineRenderingAlgorithm::Default);

private:
    Window* _window;

private:
    void draw_line(const Line& line, const Color& color);
    void draw_line_incremental(const Line& line, const Color& color);
};
