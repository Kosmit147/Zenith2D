#pragma once

#include "Zenith/Graphics/Color.hpp"
#include "Zenith/Graphics/Shapes/Shape.hpp"
#include "Zenith/Math/Geometry.hpp"
#include "Zenith/Utility/Utility.hpp"

namespace zth {

class Renderer;

class RectangleShape : public Shape
{
public:
    Rect rect{};

public:
    explicit RectangleShape() = default;
    explicit RectangleShape(const Rect& rect);
    explicit RectangleShape(const Rect& rect, const Color& color);
    ZTH_DEFAULT_COPY_DEFAULT_MOVE(RectangleShape)

    ~RectangleShape() override = default;

    void draw(Renderer& renderer) const override;

    void translate(const Vec2f& translation) override;
    void rotate(const float angle, const Vec2f& pivot_point) override;
    void scale(const float factor, const Vec2f& scaling_point) override;
    void set_color(const Color& color);
};

} // namespace zth
