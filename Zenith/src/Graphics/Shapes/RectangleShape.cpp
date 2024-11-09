#include "Zenith/Graphics/Shapes/RectangleShape.hpp"

#include "Zenith/Graphics/Renderer.hpp"

namespace zth {

RectangleShape::RectangleShape(const Rect& rect) : rect(rect) {}

RectangleShape::RectangleShape(const Rect& rect, const Color& color) : Shape(color), rect(rect) {}

void RectangleShape::draw(Renderer& renderer) const
{
    renderer.primitive_renderer().draw_filled_rect(rect, color);
}

void RectangleShape::translate(const Vec2f& translation)
{
    rect.translate(translation);
}

void RectangleShape::rotate(const float angle, const Vec2f& pivot_point)
{
    rect.rotate(angle, pivot_point);
}

void RectangleShape::scale(const float factor, const Vec2f& scaling_point)
{
    rect.scale(factor, scaling_point);
}

void RectangleShape::set_color(const Color& color)
{
    this->color = color;
}

} // namespace zth
