#pragma once

#include <memory>
#include <utility>

namespace zth {

// this is to prevent the user of the library from modifying the pointer
template<typename T> class GlobalAccessPtr
{
public:
    T& operator*() const noexcept { return *_ptr.get(); }
    T* operator->() const noexcept { return _ptr.get(); }
    explicit operator bool() const noexcept { return _ptr != nullptr; }

    T& get_or_init()
    {
        if (!_ptr)
            init();

        return *_ptr;
    }

    friend class Application;
    friend T;

private:
    std::unique_ptr<T> _ptr = nullptr;

private:
    template<typename... Args> void init(Args&&... args) { _ptr.reset(new T(std::forward<Args>(args)...)); }
    void terminate() { _ptr.reset(); }
};

} // namespace zth
