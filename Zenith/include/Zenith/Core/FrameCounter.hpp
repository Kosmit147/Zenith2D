#pragma once

#include <SFML/System/Clock.hpp>

#include "Zenith/Core/Typedefs.hpp"

namespace zth {

class FrameCounter
{
public:
    auto get_fps() const { return _fps; }

    // should be called every frame to update the counter
    void update()
    {
        _frame_count++;

        if (_clock.getElapsedTime().asSeconds() >= 1.0f)
        {
            _clock.restart();
            _fps = _frame_count;
            _frame_count = 0;
        }
    }

private:
    sf::Clock _clock;
    u32 _frame_count = 0;
    u32 _fps = 0;
};

} // namespace zth
