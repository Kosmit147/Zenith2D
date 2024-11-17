#pragma once

#include "Zenith/Graphics/Color.hpp"
#include "Zenith/Graphics/Shapes/Shape.hpp"
#include "Zenith/Math/Geometry.hpp"
#include "Zenith/Utility/Utility.hpp"

namespace zth {

class Renderer;

class EllipseShape : public Shape
{
public:
    Ellipse ellipse{};

public:
    explicit EllipseShape() = default;
    explicit EllipseShape(const Ellipse& ellipse);
    explicit EllipseShape(const Ellipse& ellipse, const Color& color);
    ZTH_DEFAULT_COPY_DEFAULT_MOVE(EllipseShape)

    ~EllipseShape() override = default;

    void draw(Renderer& renderer) const override;

    Transformable2D& translate(const Vec2f& translation) override;
    Transformable2D& rotateAroundOrigin(float angle) override;
    Transformable2D& rotate(float angle, const Vec2f& pivot_point) override;
    Transformable2D& scale(float factor, const Vec2f& scaling_point) override;
};

} // namespace zth
