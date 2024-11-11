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
    ZTH_DEFAULT_COPY_DEFAULT_MOVE(Sprite)

    ~Sprite() override = default;

    Transformable2D& translate(const Vec2f& translation) override;
    Transformable2D& rotate(float angle, const Vec2f& pivot_point) override;
    Transformable2D& scale(float factor, const Vec2f& scaling_point) override;

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
