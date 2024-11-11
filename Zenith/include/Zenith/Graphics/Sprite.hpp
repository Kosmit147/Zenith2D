#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include "Zenith/Core/Transformable.hpp"
#include "Zenith/Graphics/Animatable.hpp"
#include "Zenith/Graphics/Drawable.hpp"
#include "Zenith/Math/Geometry.hpp"
#include "Zenith/Math/Vec2.hpp"
#include "Zenith/Utility/Utility.hpp"

namespace zth {

class Renderer;
class Texture;

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
    void scale(const Vec2f& factor) override;

    void draw(Renderer& renderer) const override;

    void set_position(const Vec2f& pos) { _sprite.setPosition(static_cast<sf::Vector2f>(pos)); }
    auto get_position() const { return static_cast<Vec2f>(_sprite.getPosition()); }

    friend class Renderer;

private:
    sf::Sprite _sprite;
};

// TODO: finish this class
class AnimatedSprite : public Sprite, public Animatable
{
public:
    explicit AnimatedSprite(const Texture& texture);
    ~AnimatedSprite() override = default;

    void animate() override;
};

} // namespace zth
