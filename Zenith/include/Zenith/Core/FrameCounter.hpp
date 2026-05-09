/**
 * @file FrameCounter.hpp
 * @brief Declares the FrameCounter class for tracking frames per second (FPS).
 */

#pragma once

#include <SFML/System/Clock.hpp>
#include "Zenith/Core/Typedefs.hpp"

namespace zth {

/**
 * @class FrameCounter
 * @brief Counts and provides the frames per second (FPS) of the application.
 *
 * The FrameCounter class should be updated every frame to track and calculate the FPS,
 * which is updated once per second.
 */
class FrameCounter
{
public:
    /**
     * @brief Gets the current frames per second (FPS).
     * @return The FPS as an unsigned 32-bit integer.
     */
    auto get_fps() const { return _fps; }

    /**
     * @brief Updates the frame counter. Should be called once every frame.
     *
     * Increments the frame count and, if one second has passed, resets the frame count
     * and updates the FPS value.
     */
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
    /// The clock used to measure elapsed time.
    sf::Clock _clock;

    /// The current frame count within the current one-second interval.
    u32 _frame_count = 0;

    /// The calculated frames per second (FPS) value.
    u32 _fps = 0;
};

} // namespace zth
