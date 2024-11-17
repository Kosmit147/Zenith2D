#include "Zenith/Graphics/Shapes/TriangleShape.hpp"

#include "Zenith/Graphics/Renderer.hpp"

namespace zth {

TriangleShape::TriangleShape(const Triangle& triangle) : triangle(triangle) {}

TriangleShape::TriangleShape(const Triangle& triangle, const Color& color) : Shape(color), triangle(triangle) {}

void TriangleShape::draw(Renderer& renderer) const
{
    renderer.primitive_renderer()->draw_filled_triangle(triangle, color);
}

Transformable2D& TriangleShape::translate(const Vec2f& translation)
{
    triangle.translate(translation);
    return *this;
}

Transformable2D& TriangleShape::rotateAroundOrigin(float angle)
{

    triangle.rotateAroundOrigin(angle);
    return *this;
}

Transformable2D& TriangleShape::rotate(float angle, const Vec2f& pivot_point)
{

    triangle.rotate(angle, pivot_point);
    return *this;
}

Transformable2D& TriangleShape::scale(float factor, const Vec2f& scaling_point)
{
    triangle.scale(factor, scaling_point);
    return *this;
}

} // namespace zth
