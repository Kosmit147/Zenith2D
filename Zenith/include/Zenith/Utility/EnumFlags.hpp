#pragma once

#include <type_traits>
#include <utility>

#define ZTH_MAKE_ENUM_FLAGS(enum_t) consteval void enable_enum_flags(enum_t);

namespace zth {

template<typename T>
concept IsEnumFlags = std::is_scoped_enum_v<T> and requires(T e) { enable_enum_flags(e); };

template<IsEnumFlags T> constexpr auto operator&(T lhs, T rhs)
{
    return static_cast<T>(std::to_underlying(lhs) & std::to_underlying(rhs));
}

template<IsEnumFlags T> constexpr auto operator|(T lhs, T rhs)
{
    return static_cast<T>(std::to_underlying(lhs) | std::to_underlying(rhs));
}

template<IsEnumFlags T> constexpr auto operator^(T lhs, T rhs)
{
    return static_cast<T>(std::to_underlying(lhs) ^ std::to_underlying(rhs));
}

template<IsEnumFlags T> constexpr auto operator~(T val)
{
    return static_cast<T>(~std::to_underlying(val));
}

template<IsEnumFlags T> constexpr T& operator&=(T& lhs, T rhs)
{
    return lhs = lhs & rhs;
}

template<IsEnumFlags T> constexpr T& operator|=(T& lhs, T rhs)
{
    return lhs = lhs | rhs;
}

template<IsEnumFlags T> constexpr T& operator^=(T& lhs, T rhs)
{
    return lhs = lhs ^ rhs;
}

template<IsEnumFlags T> auto operator==(T, T) = delete;
template<IsEnumFlags T> auto operator!=(T, T) = delete;

template<IsEnumFlags T>
constexpr bool has_flag(T val, T flag)
{
    return static_cast<bool>(val & flag);
}

template<IsEnumFlags T, IsEnumFlags... Flags>
constexpr bool has_flags(T val, Flags... flags)
    requires(std::conjunction_v<std::is_same<T, Flags>...>)
{
    T sum = (flags | ...);
    return (val & sum) == sum;
}

template<IsEnumFlags T, IsEnumFlags... Flags>
constexpr bool has_any_flag(T val, Flags... flags)
    requires(std::conjunction_v<std::is_same<T, Flags>...>)
{
    T sum = (flags | ...);
    return static_cast<bool>(val & sum);
}

} // namespace zth
