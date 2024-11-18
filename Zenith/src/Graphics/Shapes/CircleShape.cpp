#include "Zenith/Graphics/Shapes/CircleShape.hpp"

#include "Zenith/Graphics/Renderer.hpp"

namespace zth {

CircleShape::CircleShape(const Circle& circle) : circle(circle) {}

CircleShape::CircleShape(const Circle& circle, const Color& color) : Shape(color), circle(circle) {}

void CircleShape::draw(Renderer& renderer) const
{
    renderer.primitive_renderer()->draw_filled_circle(circle, color);
}

Transformable2D& CircleShape::translate(const Vec2f& translation)
{
    circle.translate(translation);
    return *this;
}

Transformable2D& CircleShape::rotate(float angle)
{
    circle.rotate(angle);
    return *this;
}

Transformable2D& CircleShape::rotate(float angle, const Vec2f& pivot_point)
{
    circle.rotate(angle, pivot_point);
    return *this;
}

Transformable2D& CircleShape::scale(float factor)
{
    circle.scale(factor);
    return *this;
}

Transformable2D& CircleShape::scale(float factor, const Vec2f& scaling_point)
{
    circle.scale(factor, scaling_point);
    return *this;
}

} // namespace zth
