#pragma once

#include <SFML/Graphics.hpp>

#include <span>

#include "Window.h"
#include "Geometry.h"

enum class LineRenderingAlgorithm
{
    Default,
    Incremental,
};

class PrimitiveRenderer
{
public:
    inline PrimitiveRenderer(Window* window) : _window(window) {}

    void draw(Point2D point);
    void draw(const Line& line, LineRenderingAlgorithm alg = LineRenderingAlgorithm::Default);
    void draw(std::span<Line> lines, LineRenderingAlgorithm alg = LineRenderingAlgorithm::Default);

private:
    Window* _window;
};
