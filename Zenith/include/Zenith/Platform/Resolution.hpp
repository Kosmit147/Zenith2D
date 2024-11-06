#pragma once

#include <SFML/Window/VideoMode.hpp>

#include "Zenith/Core/Typedefs.hpp"

namespace zth {

struct Resolution
{
    u32 width;
    u32 height;

    explicit operator sf::VideoMode() const { return sf::VideoMode{ width, height }; }
};

} // namespace zth
