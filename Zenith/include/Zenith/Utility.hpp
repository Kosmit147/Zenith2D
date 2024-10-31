#pragma once

#define ZTH_NO_COPY(type)                                                                                              \
    type(const type&) = delete;                                                                                        \
    auto operator=(const type&) = delete;

#define ZTH_NO_MOVE(type)                                                                                              \
    type(type&&) = delete;                                                                                             \
    auto operator=(type&&) = delete;

#define ZTH_NO_COPY_NO_MOVE(type)                                                                                      \
    ZTH_NO_COPY(type)                                                                                                  \
    ZTH_NO_MOVE(type)
