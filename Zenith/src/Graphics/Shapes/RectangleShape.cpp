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
    rect.translate_rect(translation);
}

void RectangleShape::rotate(const float& angle, const Vec2f& pivot_point)
{
    rect.rotate_rect(angle, pivot_point);
}

void RectangleShape::scale(const float& factor, const Vec2f& scaling_point)
{
    rect.scale_rect(factor, scaling_point);
}

} // namespace zth
