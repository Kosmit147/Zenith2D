#pragma once

#include <Zenith/Core/Application.hpp>

class Testbed : public zth::Application
{
public:
    Testbed();
    ~Testbed() override;

private:
    void on_update() override;
    void on_event(const zth::Event& event) override;

    void primitive_renderer_test() const;
    static void event_test(const zth::Event& event);
};
