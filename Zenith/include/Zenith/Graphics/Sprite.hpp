/**
 * @file Sprite.hpp
 * @brief Defines the `Sprite` and `AnimatedSprite` classes for rendering 2D sprites and animations in a graphics system.
 */

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

class Texture;

/**
 * @struct SpriteSize
 * @brief Holds the dimensions of a sprite in pixels (width and height).
 */
struct SpriteSize
{
    u32 width; ///< The width of the sprite in pixels.
    u32 height; ///< The height of the sprite in pixels.
};

/**
 * @class Sprite
 * @brief A 2D sprite that can be rendered to the screen, with support for basic transformations (translate, rotate, scale).
 * 
 * The `Sprite` class is a wrapper around SFML's `sf::Sprite` with additional functionality to transform and draw the sprite.
 * It includes basic methods for translating, rotating, and scaling the sprite.
 */
class Sprite : public Drawable, public Transformable2D
{
public:
    /**
     * @brief Default constructor for `Sprite`.
     */
    explicit Sprite() = default;

    /**
     * @brief Constructs a `Sprite` with a specified texture and optional texture rectangle.
     * @param texture The texture to be applied to the sprite.
     * @param texture_rect The rectangle of the texture to use (defaults to the whole texture).
     */
    explicit Sprite(const Texture& texture, const IntRect& texture_rect = { { 0, 0 }, { 0, 0 } });

    /**
     * @brief Deleted constructor to prevent moving temporary textures into the sprite.
     */
    explicit Sprite(Texture&&) = delete;

    /**
     * @brief Deleted constructor to prevent moving temporary textures with a texture rectangle into the sprite.
     */
    explicit Sprite(Texture&&, const IntRect&) = delete;

    /**
     * @brief Default copy constructor and move constructor.
     */
    ZTH_DEFAULT_COPY_DEFAULT_MOVE(Sprite)

    /**
     * @brief Destructor for `Sprite`.
     */
    ~Sprite() override = default;

    /**
     * @brief Translates the sprite by the specified vector.
     * @param translation The translation vector.
     * @return A reference to the `Transformable2D` object.
     */
    Transformable2D& translate(const Vec2f& translation) override;

    /**
     * @brief Rotates the sprite by the specified angle (in degrees).
     * @param angle The angle of rotation (in degrees).
     * @return A reference to the `Transformable2D` object.
     */
    Transformable2D& rotate(float angle) override;

    /**
     * @brief Rotates the sprite by the specified angle around a given pivot point.
     * @param angle The angle of rotation (in degrees).
     * @param pivot_point The point around which the sprite will rotate.
     * @return A reference to the `Transformable2D` object.
     */
    Transformable2D& rotate(float angle, const Vec2f& pivot_point) override;

    /**
     * @brief Scales the sprite by the specified factor.
     * @param factor The scaling factor.
     * @return A reference to the `Transformable2D` object.
     */
    Transformable2D& scale(float factor) override;

    /**
     * @brief Scales the sprite by the specified factor around a given scaling point.
     * @param factor The scaling factor.
     * @param scaling_point The point around which the sprite will scale.
     * @return A reference to the `Transformable2D` object.
     */
    Transformable2D& scale(float factor, const Vec2f& scaling_point) override;

    /**
     * @brief Draws the sprite to the screen using the provided renderer.
     * @param renderer The renderer to draw the sprite with.
     */
    void draw(Renderer& renderer) const override;

    /**
     * @brief Sets the position of the sprite.
     * @param pos The new position for the sprite.
     */
    void set_position(const Vec2f& pos) { _sprite.setPosition(static_cast<sf::Vector2f>(pos)); }

    /**
     * @brief Gets the current position of the sprite.
     * @return The current position of the sprite.
     */
    auto get_position() const { return static_cast<Vec2f>(_sprite.getPosition()); }

    /**
     * @brief Gets the bounding box of the sprite.
     * @return The bounding box of the sprite as a `Rect`.
     */
    auto bounds() const { return Rect::from_sf_rect(_sprite.getGlobalBounds()); }

    /**
     * @brief Sets the texture rectangle (part of the texture to use) for the sprite.
     * @param texture_rect The rectangle of the texture to use.
     */
    void set_texture_rect(const IntRect& texture_rect);

    friend class Renderer;

private:
    sf::Sprite _sprite; ///< The underlying SFML sprite object.
};

/**
 * @class AnimatedSprite
 * @brief A sprite with animation support, capable of cycling through frames in a sprite sheet.
 * 
 * The `AnimatedSprite` class extends the `Sprite` class by adding animation functionality. It can animate by cycling through frames
 * in a sprite sheet.
 */
class AnimatedSprite : public Sprite, public Animatable
{
public:
    /**
     * @brief Constructs an animated sprite with a specified texture, sprite size, number of frames, and frame length.
     * @param texture The texture for the sprite.
     * @param sprite_size The size of each sprite frame.
     * @param frames The number of frames in the sprite sheet.
     * @param frame_length_seconds The length of each frame in seconds.
     */
    explicit AnimatedSprite(const Texture& texture, const SpriteSize& sprite_size, u32 frames,
                            float frame_length_seconds);

    /**
     * @brief Default copy constructor and move constructor.
     */
    ZTH_DEFAULT_COPY_DEFAULT_MOVE(AnimatedSprite)

    /**
     * @brief Destructor for `AnimatedSprite`.
     */
    ~AnimatedSprite() override = default;

    /**
     * @brief Starts or continues the animation by cycling through frames.
     */
    void animate() override;

private:
    u32 _current_frame = 0; ///< The current frame in the animation.
    u32 _frames; ///< The total number of frames in the animation.
    SpriteSize _sprite_size; ///< The size of each sprite frame.
    u32 _sprite_sheet_cols; ///< The number of columns in the sprite sheet.
    u32 _sprite_sheet_rows; ///< The number of rows in the sprite sheet.

    sf::Clock _frame_timer; ///< A clock to time frame changes.
    sf::Time _frame_length; ///< The length of time each frame is displayed.

private:
    /**
     * @brief Updates the texture rectangle to show the next frame in the animation.
     */
    void update_animation_texture_rect();

    /**
     * @brief Determines the next frame in the animation cycle.
     * @return The next frame number.
     */
    virtual u32 next_frame();
};

} // namespace zth
