#pragma once

#include <Zenith/Application.h>

class Application : public zth::Application
{
public:
    Application();
    ~Application();

    void on_update(zth::u64 delta_time) override;
    void on_event(const zth::Event& event) override;
};