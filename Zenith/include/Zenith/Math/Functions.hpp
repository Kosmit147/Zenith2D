#pragma once

namespace zth {

template<typename T> constexpr T abs(T val)
{
    return val < 0 ? -val : val;
}

} // namespace zth
