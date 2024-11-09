#pragma once

#include <Zenith/Zenith.hpp>

class Player : public zth::Updatable, public zth::EventListener, public zth::Sprite
{
public:
    float movement_speed = 1000.0f;

public:
    explicit Player() = default;
    explicit Player(const zth::Texture& texture);

    void on_update() override;
    void on_event(const zth::Event& event) override;
    void on_key_pressed(const zth::KeyEvent& event);
};
