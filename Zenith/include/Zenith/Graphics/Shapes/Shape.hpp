#pragma once

#include "Zenith/Core/Transformable.hpp"
#include "Zenith/Graphics/Color.hpp"
#include "Zenith/Graphics/Drawable.hpp"
#include "Zenith/Utility/Utility.hpp"

namespace zth {

class Shape : public Drawable, public Transformable2D
{
public:
    Color color = Color::white;

public:
    explicit Shape() = default;
    explicit Shape(const Color& color) : color(color) {}
    ZTH_DEFAULT_COPY_DEFAULT_MOVE(Shape)

    ~Shape() override = default;
};

} // namespace zth
