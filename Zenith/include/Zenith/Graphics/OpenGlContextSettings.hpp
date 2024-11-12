#pragma once

#include <SFML/Window/ContextSettings.hpp>

#include "Zenith/Core/Typedefs.hpp"

namespace zth {

struct OpenGlVersion
{
    u32 major;
    u32 minor;
};

struct OpenGlContextSettings
{
    OpenGlVersion version;
    u32 depth_bits;
    u32 stencil_bits;
    u32 antialiasing_level;
    u32 attributes;
    bool s_rgb_capable;

    explicit operator sf::ContextSettings() const
    {
        return sf::ContextSettings(depth_bits, stencil_bits, antialiasing_level, version.major, version.minor,
                                   attributes, s_rgb_capable);
    }
};

}; // namespace zth
