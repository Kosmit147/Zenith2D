#pragma once

#include <Zenith/Core/Application.hpp>

#include "Player.hpp"

class Application : public zth::Application
{
public:
    Application();
    ~Application() override;

private:
    Player _player;

private:
    void on_update(double delta_time) override;
    void on_event(const zth::Event& event, double delta_time) override;
};
