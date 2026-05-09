/**
 * @file OpenGlContextSettings.hpp
 * @brief Defines structures for OpenGL context settings.
 */

#pragma once

#include <SFML/Window/ContextSettings.hpp>

#include "Zenith/Core/Typedefs.hpp"

namespace zth {

/**
 * @struct OpenGlVersion
 * @brief Represents the version of OpenGL.
 *
 * This structure holds the major and minor version numbers of an OpenGL context.
 */
struct OpenGlVersion
{
    u32 major; ///< Major version number of OpenGL.
    u32 minor; ///< Minor version number of OpenGL.
};

/**
 * @struct OpenGlContextSettings
 * @brief Represents the settings required for an OpenGL context.
 *
 * This structure defines various settings for creating an OpenGL context, such as the OpenGL version,
 * depth bits, stencil bits, antialiasing level, and other OpenGL attributes.
 */
struct OpenGlContextSettings
{
    OpenGlVersion version; ///< The OpenGL version.
    u32 depth_bits; ///< The number of bits for depth buffer precision.
    u32 stencil_bits; ///< The number of bits for stencil buffer precision.
    u32 antialiasing_level; ///< The level of antialiasing (e.g., 0 for no antialiasing).
    u32 attributes; ///< Additional OpenGL context attributes.
    bool s_rgb_capable; ///< Whether the context supports sRGB color.

    /**
     * @brief Converts the OpenGlContextSettings to an SFML ContextSettings.
     * @return The equivalent SFML ContextSettings object.
     *
     * This method converts the `OpenGlContextSettings` structure into an `sf::ContextSettings`
     * object, which can be used when creating an SFML window with specific OpenGL context settings.
     */
    explicit operator sf::ContextSettings() const
    {
        return sf::ContextSettings(depth_bits, stencil_bits, antialiasing_level, version.major, version.minor,
                                   attributes, s_rgb_capable);
    }
};

}; // namespace zth
