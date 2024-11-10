#pragma once

#include <Zenith/Zenith.hpp>

#include "Player.hpp"

class Scene : public zth::Scene
{
public:
    explicit Scene();
    ~Scene() override;

private:
    zth::Texture _player_texture = zth::Texture::from_file("assets/emoji.png").value_or(zth::Texture{});
    Player _player{ _player_texture };

private:
    void on_update() override;
};
