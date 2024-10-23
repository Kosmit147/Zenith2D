#pragma once

#include <chrono>

#include "Typedefs.hpp"

namespace zth {

class Timer
{
public:
    inline Timer() { reset(); }

    inline void reset() { _start = std::chrono::high_resolution_clock::now(); }

    inline usize elapsed_ns() const
    {
        auto ns =
            std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - _start);
        return ns.count();
    }

    inline double elapsed_ms() const { return elapsed_ns() / 1000000.0; }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> _start;
};

} // namespace zth
