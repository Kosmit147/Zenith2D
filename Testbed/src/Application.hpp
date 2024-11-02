#pragma once

#include <Zenith/Core/Application.hpp>

class Application : public zth::Application
{
public:
    Application();
    ~Application() override;

private:
    void on_update(zth::u64 delta_time) override;
    void on_event(const zth::Event& event) override;
};
