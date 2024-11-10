#pragma once

#include <Zenith/Zenith.hpp>

class Player : public zth::Sprite, public zth::Updatable
{
public:
    explicit Player(const zth::Texture& texture);

    void on_update() override;

private:
    float _movement_speed = 1000.0f;
};
