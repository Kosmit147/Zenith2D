#pragma once

#include "Zenith/Graphics/Color.hpp"
#include "Zenith/Graphics/Shapes/Shape.hpp"
#include "Zenith/Math/Geometry.hpp"
#include "Zenith/Utility/Utility.hpp"

namespace zth {

class Renderer;

class TriangleShape : public Shape
{
public:
    Triangle triangle{};

public:
    explicit TriangleShape() = default;
    explicit TriangleShape(const Triangle& triangle);
    explicit TriangleShape(const Triangle& triangle, const Color& color);
    ZTH_DEFAULT_COPY_DEFAULT_MOVE(TriangleShape)

    ~TriangleShape() override = default;

    void draw(Renderer& renderer) const override;

    Transformable2D& translate(const Vec2f& translation) override;
    Transformable2D& rotate(float angle) override;
    Transformable2D& rotate(float angle, const Vec2f& pivot_point) override;
    Transformable2D& scale(float factor) override;
    Transformable2D& scale(float factor, const Vec2f& scaling_point) override;
};

} // namespace zth
