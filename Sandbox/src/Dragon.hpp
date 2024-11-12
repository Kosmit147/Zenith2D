#pragma once

#include <Zenith/Zenith.hpp>

enum class Direction
{
    Up,
    Right,
    Down,
    Left,
};

class Dragon : public zth::AnimatedSprite, public zth::Updatable
{
public:
    explicit Dragon(const zth::Texture& texture);

    void on_update() override;

private:
    float _movement_speed = 700.0f;
    bool _walking = false;
    Direction _direction = Direction::Down;
    float _walking_animation_length = 0.15f;

private:
    zth::u32 next_frame() override;
};
