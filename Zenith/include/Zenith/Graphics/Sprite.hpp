#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

#include "Zenith/Core/Transformable.hpp"
#include "Zenith/Core/Typedefs.hpp"
#include "Zenith/Graphics/Animatable.hpp"
#include "Zenith/Graphics/Drawable.hpp"
#include "Zenith/Math/Geometry.hpp"
#include "Zenith/Math/Vec2.hpp"
#include "Zenith/Utility/Utility.hpp"

namespace zth {

class Renderer;
class Texture;

struct SpriteSize
{
    u32 width;
    u32 height;
};

class Sprite : public Drawable, public Transformable2D
{
public:
    explicit Sprite() = default;
    explicit Sprite(const Texture& texture, const IntRect& texture_rect = { { 0, 0 }, { 0, 0 } });

    // creating a sprite from a temporary texture is a mistake,
    // because the texture must live as long as the sprite
    explicit Sprite(Texture&&) = delete;
    explicit Sprite(Texture&&, const IntRect&) = delete;

    ZTH_DEFAULT_COPY_DEFAULT_MOVE(Sprite)

    ~Sprite() override = default;

    void translate(const Vec2f& translation) override;
    void rotate(float angle) override;
    void scale(float factor);
    void scale(const Vec2f& factor) override;

    void draw(Renderer& renderer) const override;

    void set_position(const Vec2f& pos) { _sprite.setPosition(static_cast<sf::Vector2f>(pos)); }
    auto get_position() const { return static_cast<Vec2f>(_sprite.getPosition()); }

    auto bounds() const { return Rect::from_sf_rect(_sprite.getGlobalBounds()); }

    void set_texture_rect(const IntRect& texture_rect);

    friend class Renderer;

private:
    sf::Sprite _sprite;
};

class AnimatedSprite : public Sprite, public Animatable
{
public:
    explicit AnimatedSprite(const Texture& texture, const SpriteSize& sprite_size, u32 frames,
                            float frame_length_seconds);

    ZTH_DEFAULT_COPY_DEFAULT_MOVE(AnimatedSprite)

    ~AnimatedSprite() override = default;

    void animate() override;

private:
    u32 _current_frame = 0;
    u32 _frames;
    SpriteSize _sprite_size;
    u32 _sprite_sheet_cols;
    u32 _sprite_sheet_rows;

    sf::Clock _frame_timer;
    sf::Time _frame_length;

private:
    void update_animation_texture_rect();
    virtual u32 next_frame();
};

} // namespace zth
