#include "Zenith/Core/Scene.hpp"

namespace zth {

void Scene::register_updatable(Updatable& updatable)
{
    _updater.register_updatable(updatable);
}

void Scene::deregister_updatable(const Updatable& updatable)
{
    _updater.deregister_updatable(updatable);
}

void Scene::register_event_listener(EventListener& listener)
{
    _event_dispatcher.register_listener(listener);
}

void Scene::register_event_listener(EventType event_type, EventListener& listener)
{
    _event_dispatcher.register_listener(event_type, listener);
}

void Scene::deregister_event_listener(EventType event_type, const EventListener& listener)
{
    _event_dispatcher.deregister_listener(event_type, listener);
}

void Scene::deregister_event_listener(const EventListener& listener)
{
    _event_dispatcher.deregister_listener(listener);
}

void Scene::update()
{
    on_update();
    _updater.update();
}

void Scene::dispatch_event(const Event& event)
{
    on_event(event);
    _event_dispatcher.dispatch(event);
}

} // namespace zth
