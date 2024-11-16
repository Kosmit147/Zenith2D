#pragma once

#include <Zenith/Zenith.hpp>

#include "Player.hpp"
#include "Dragon.hpp"

class Scene : public zth::Scene
{
public:
    explicit Scene();
    ~Scene() override;

private:
    zth::Texture _dragon_texture;
    Dragon _dragon;
    zth::Texture _player_texture;
    Player _player;

private:
    void on_update() override;
};
