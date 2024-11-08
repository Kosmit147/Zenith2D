#pragma once

#include <chrono>

#include "Zenith/Core/Typedefs.hpp"

namespace zth {

class Timer
{
public:
    Timer() { reset(); }

    void reset() { _start = std::chrono::high_resolution_clock::now(); }

    usize elapsed_ns() const
    {
        auto ns =
            std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - _start);
        return static_cast<usize>(ns.count());
    }

    double elapsed_ms() const { return static_cast<double>(elapsed_ns()) / 1000.0 / 1000.0; }
    double elapsed_s() const { return elapsed_ms() / 1000.0; }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> _start;
};

} // namespace zth
