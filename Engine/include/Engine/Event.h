#pragma once

#include <SFML/Window/Event.hpp>

#include <cassert>
#include <optional>
#include <variant>

#include "Key.h"

struct KeyEvent
{
    Key key;
};

enum class EventType
{
    KeyPressed,
    KeyReleased,
    WindowClosed,
};

class Event
{
public:
    static std::optional<Event> create_from_sf_event(const sf::Event& event);

    inline auto type() const { return _type; }

    inline const KeyEvent& key_event() const
    {
        assert(_type == EventType::KeyPressed || _type == EventType::KeyReleased);
        return _key_event;
    }

private:
    inline Event(EventType event_type) : _type(event_type), _dummy() {}
    inline Event(EventType event_type, KeyEvent key_event) : _type(event_type), _key_event(key_event) {}

private:
    EventType _type;

    union
    {
        std::monostate _dummy;
        KeyEvent _key_event;
    };
};
