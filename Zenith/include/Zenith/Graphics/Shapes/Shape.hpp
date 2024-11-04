#pragma once

#include "Zenith/Core/Transformable.hpp"
#include "Zenith/Graphics/Color.hpp"
#include "Zenith/Graphics/Drawable.hpp"

namespace zth {

class Shape : public Drawable, public Transformable2D
{
public:
    Color color = Color::white;

public:
    explicit Shape() = default;
    explicit Shape(const Color& color) : color(color) {}
    ~Shape() override = default;
};

} // namespace zth
