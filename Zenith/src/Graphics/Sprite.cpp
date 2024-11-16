#include "Zenith/Graphics/Sprite.hpp"

#include "Zenith/Graphics/Renderer.hpp"
#include "Zenith/Graphics/Texture.hpp"

namespace zth {

Sprite::Sprite(const Texture& texture, const IntRect& texture_rect)
    : _sprite(texture._texture, static_cast<sf::IntRect>(texture_rect))
{}

Transformable2D& Sprite::translate(const Vec2f& translation)
{
    (void)translation;
    // TODO
    return *this;
    _sprite.move(static_cast<sf::Vector2f>(translation));
}

Transformable2D& Sprite::rotate(float angle, const Vec2f& pivot_point)
{
    (void)angle;
    (void)pivot_point;
    // TODO
    return *this;
    _sprite.rotate(angle);
}

Transformable2D& Sprite::scale(float factor, const Vec2f& scaling_point)
{
    (void)factor;
    (void)scaling_point;
    // TODO
    return *this;
    _sprite.setScale(static_cast<sf::Vector2f>(factor));
}

void Sprite::draw(Renderer& renderer) const
{
    renderer.draw_sprite(*this);
}

void Sprite::set_texture_rect(const IntRect& texture_rect)
{
    _sprite.setTextureRect(static_cast<sf::IntRect>(texture_rect));
}

AnimatedSprite::AnimatedSprite(const Texture& texture, const SpriteSize& sprite_size, u32 frames,
                               float frame_length_seconds)
    : Sprite(texture), _frames(frames), _sprite_size(sprite_size), _frame_length(sf::seconds(frame_length_seconds))
{
    set_texture_rect({ .position = { 0, 0 },
                       .size = { static_cast<i32>(sprite_size.width), static_cast<i32>(sprite_size.height) } });

    const auto [tex_width, tex_height] = texture.size();
    _sprite_sheet_cols = tex_width / _sprite_size.width;
    _sprite_sheet_rows = tex_height / _sprite_size.height;
}

void AnimatedSprite::animate()
{
    if (_frame_timer.getElapsedTime() > _frame_length)
    {
        _frame_timer.restart();
        _current_frame = next_frame() % _frames;
        update_animation_texture_rect();
    }
}

void AnimatedSprite::update_animation_texture_rect()
{
    auto x = static_cast<i32>(_current_frame % _sprite_sheet_cols * _sprite_size.width);
    auto y = static_cast<i32>(_current_frame / _sprite_sheet_cols * _sprite_size.height);

    set_texture_rect({ .position = { x, y },
                       .size = { static_cast<i32>(_sprite_size.width), static_cast<i32>(_sprite_size.height) } });
}

u32 AnimatedSprite::next_frame()
{
    return _current_frame + 1;
}

} // namespace zth
