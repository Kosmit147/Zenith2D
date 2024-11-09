#include "Zenith/Core/Engine.hpp"

#include "Zenith/Logging/Logger.hpp"

namespace zth {

Engine::~Engine()
{
    logger.get_or_init().log_notification("Engine shut down.");
}

void Engine::register_updatable(Updatable& updatable)
{
    _updater.register_updatable(updatable);
}

void Engine::deregister_updatable(const Updatable& updatable)
{
    _updater.deregister_updatable(updatable);
}

void Engine::register_listener(EventListener& listener)
{
    _event_dispatcher.register_listener(listener);
}

void Engine::register_listener(EventType event_type, EventListener& listener)
{
    _event_dispatcher.register_listener(event_type, listener);
}

void Engine::deregister_listener(EventType event_type, const EventListener& listener)
{
    _event_dispatcher.deregister_listener(event_type, listener);
}

void Engine::deregister_listener(const EventListener& listener)
{
    _event_dispatcher.deregister_listener(listener);
}

Engine::Engine(const WindowSpec& window_spec) : window(window_spec)
{
    logger.get_or_init().log_notification("Engine initialized.");
}

} // namespace zth
