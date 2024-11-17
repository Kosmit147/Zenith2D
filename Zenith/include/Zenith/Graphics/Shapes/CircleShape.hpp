#pragma once

#include "Zenith/Graphics/Color.hpp"
#include "Zenith/Graphics/Shapes/Shape.hpp"
#include "Zenith/Math/Geometry.hpp"
#include "Zenith/Utility/Utility.hpp"

namespace zth {

class Renderer;

class CircleShape : public Shape
{
public:
    Circle circle{};

public:
    explicit CircleShape() = default;
    explicit CircleShape(const Circle& circle);
    explicit CircleShape(const Circle& circle, const Color& color);
    ZTH_DEFAULT_COPY_DEFAULT_MOVE(CircleShape)

    ~CircleShape() override = default;

    void draw(Renderer& renderer) const override;

    Transformable2D& translate(const Vec2f& translation) override;
    Transformable2D& rotateAroundOrigin(float angle) override;
    Transformable2D& rotate(float angle, const Vec2f& pivot_point) override;
    Transformable2D& scale(float factor, const Vec2f& scaling_point) override;
};

} // namespace zth
