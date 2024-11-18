#pragma once

#include <Zenith/Zenith.hpp>

class Level2 : public zth::Scene
{
public:
    explicit Level2();
    ~Level2() override = default;

private:
    zth::Texture _you_won_texture;
    zth::Sprite _you_won;

private:
    void on_update() override {}
};
