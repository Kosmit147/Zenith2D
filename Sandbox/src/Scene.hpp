#pragma once

#include <Zenith/Zenith.hpp>

#include "Player.hpp"

class Scene : public zth::Scene
{
public:
    explicit Scene();
    ~Scene() override;

private:
    zth::Texture _player_texture;
    Player _player;

private:
    void on_update() override;
};
