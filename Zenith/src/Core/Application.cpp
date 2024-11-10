#include "Zenith/Core/Application.hpp"

#include <SFML/System/Clock.hpp>

#include "Zenith/Core/Engine.hpp"
#include "Zenith/Logging/Logger.hpp"

namespace zth {

Application::Application(const ApplicationSpec& spec)
{
    // logger should be initialized first
    logger.init(spec.logger_spec);
    engine.init(spec.window_spec);
}

Application::~Application()
{
    engine.terminate();
    logger.terminate();
}

void Application::run()
{
    sf::Clock delta_t_clock;

    while (engine->window.is_open())
    {
        engine->_delta_time = delta_t_clock.restart().asMilliseconds() / 1000.0;
        engine->window.clear();

        while (auto event = engine->window.poll_event())
        {
            const auto& ev = event.value();

            if (ev.type() == EventType::WindowClosed)
            {
                handle_event(ev);
                engine->window.close();
                return;
            }

            handle_event(ev);
        }

        handle_update();
        engine->window.display();
        engine->_frame_counter.update();
    }
}

void Application::handle_update()
{
    on_update();
    engine->on_update();
}

void Application::handle_event(const Event& event)
{
    on_event(event);
    engine->on_event(event);
}

} // namespace zth
