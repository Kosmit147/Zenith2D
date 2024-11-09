#pragma once

#include <Zenith/Zenith.hpp>

#include "Player.hpp"

class Sandbox : public zth::Application
{
public:
    Sandbox();
    ~Sandbox() override;

private:
    zth::Texture _player_texture;
    Player _player;

private:
    void on_update() override;
    void on_event(const zth::Event& event) override;
};
