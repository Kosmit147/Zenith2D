#include "Zenith/Graphics/Shapes/RectangleShape.hpp"

#include "Zenith/Graphics/PrimitiveRenderer.hpp"

namespace zth {

RectangleShape::RectangleShape(const Rect& rect) : rect(rect) {}

RectangleShape::RectangleShape(const Rect& rect, const Color& color) : Shape(color), rect(rect) {}

void RectangleShape::draw(PrimitiveRenderer& renderer) const
{
    renderer.draw_filled_rect(rect, color);
}

void RectangleShape::translate(const Vec2f& translation)
{
    (void)translation;
    // TODO
}

void RectangleShape::rotate(float angle)
{
    (void)angle;
    // TODO
}

void RectangleShape::scale(const Vec2f& factor)
{
    (void)factor;
    // TODO
}

} // namespace zth