#include "Zenith/Graphics/Sprite.hpp"

#include "Zenith/Graphics/Renderer.hpp"
#include "Zenith/Graphics/Texture.hpp"

namespace zth {

Sprite::Sprite(const Texture& texture, const IntRect& texture_rect)
    : _sprite(texture._texture, static_cast<sf::IntRect>(texture_rect))
{}

void Sprite::translate(const Vec2f& translation)
{
    (void)translation;
    // TODO
}

void Sprite::rotate(const float angle, const Vec2f& pivot_point)
{
    (void)angle;
    (void)pivot_point;
    // TODO
}

void Sprite::scale(const float factor, const Vec2f& scaling_point)
{
    (void)factor;
    (void)scaling_point;
    // TODO
}

void Sprite::draw(Renderer& renderer) const
{
    renderer.draw_sprite(*this);
}

} // namespace zth
