#pragma once

#include <cstdint>

enum class LogSeverity
{
    Notification,
    Warning,
    Error,
};

using LogTargetType = uint32_t;

enum class LogTarget : LogTargetType
{
    None = 0,
    Console = 1 << 0,
    File = 1 << 1,
    ConsoleAndFile = Console | File,
};

constexpr inline LogTargetType operator&(LogTarget lhs, LogTarget rhs)
{
    return static_cast<LogTargetType>(lhs) & static_cast<LogTargetType>(rhs);
}

constexpr inline LogTargetType operator|(LogTarget lhs, LogTarget rhs)
{
    return static_cast<LogTargetType>(lhs) | static_cast<LogTargetType>(rhs);
}

LogTargetType operator==(LogTarget, LogTarget) = delete;
LogTargetType operator!=(LogTarget, LogTarget) = delete;
