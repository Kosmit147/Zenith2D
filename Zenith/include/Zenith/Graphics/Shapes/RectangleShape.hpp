#pragma once

#include "Zenith/Graphics/Color.hpp"
#include "Zenith/Graphics/Shapes/Shape.hpp"
#include "Zenith/Math/Geometry.hpp"

namespace zth {

class RectangleShape : public Shape
{
public:
    Rect rect{};

public:
    explicit RectangleShape() = default;
    explicit RectangleShape(const Rect& rect);
    explicit RectangleShape(const Rect& rect, const Color& color);

    ~RectangleShape() override = default;

    void draw(PrimitiveRenderer& renderer) const override;

    void translate(const Vec2f& translation) override;
    void rotate(float angle) override;
    void scale(const Vec2f& factor) override;
};

} // namespace zth
