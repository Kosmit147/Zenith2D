#include "Event.h"

std::optional<Event> Event::create_from_sf_event(const sf::Event& event)
{
    std::optional<Event> ret = {};

    switch (event.type)
    {
    case sf::Event::KeyPressed:
        ret = { EventType::KeyPressed, KeyEvent { .key = key_from_sf_scancode(event.key.scancode) } };
        break;
    case sf::Event::KeyReleased:
        ret = { EventType::KeyReleased, KeyEvent { .key = key_from_sf_scancode(event.key.scancode) } };
        break;
    }

    return ret;
}
