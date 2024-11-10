#pragma once

#include <Zenith/Zenith.hpp>

class Sandbox : public zth::Application
{
public:
    Sandbox();
    ~Sandbox() override;

private:
    void on_update() override;
    void on_event(const zth::Event& event) override;
};
