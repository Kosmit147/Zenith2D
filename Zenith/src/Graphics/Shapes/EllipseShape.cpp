#include "Zenith/Graphics/Shapes/EllipseShape.hpp"

#include "Zenith/Graphics/Renderer.hpp"

namespace zth {

EllipseShape::EllipseShape(const Ellipse& ellipse) : ellipse(ellipse) {}

EllipseShape::EllipseShape(const Ellipse& ellipse, const Color& color) : Shape(color), ellipse(ellipse) {}

void EllipseShape::draw(Renderer& renderer) const
{
    renderer.primitive_renderer()->draw_filled_ellipse(ellipse, color);
}

Transformable2D& EllipseShape::translate(const Vec2f& translation)
{
    ellipse.translate(translation);
    return *this;
}

Transformable2D& EllipseShape::rotate(float angle)
{
    ellipse.rotate(angle);
    return *this;
}

Transformable2D& EllipseShape::rotate(float angle, const Vec2f& pivot_point)
{
    ellipse.rotate(angle, pivot_point);
    return *this;
}

Transformable2D& EllipseShape::scale(float factor)
{
    ellipse.scale(factor);
    return *this;
}

Transformable2D& EllipseShape::scale(float factor, const Vec2f& scaling_point)
{
    ellipse.scale(factor, scaling_point);
    return *this;
}

} // namespace zth
