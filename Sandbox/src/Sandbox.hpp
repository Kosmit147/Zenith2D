#pragma once

#include <Zenith/Core/Application.hpp>
#include <Zenith/Graphics/Texture.hpp>

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
    void on_update(double delta_time) override;
    void on_event(const zth::Event& event, double delta_time) override;
};
