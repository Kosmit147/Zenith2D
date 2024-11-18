#pragma once

#include <Zenith/Zenith.hpp>

#include "Player.hpp"
#include "Dragon.hpp"

class Level1 : public zth::Scene
{
public:
    explicit Level1();
    ~Level1() override;

private:
    zth::Texture _dragon_texture;
    Dragon _dragon;
    zth::Texture _player_texture;
    Player _player;
    zth::Texture _gold_bars_texture;
    zth::Sprite _gold_bars;

private:
    void on_update() override;
};
