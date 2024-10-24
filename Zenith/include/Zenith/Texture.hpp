#pragma once

#include <filesystem>
#include <span>
#include <vector>

#include "Typedefs.hpp"

namespace zth {

class Texture
{
public:
    inline Texture() : _data(), _width(0), _height(0) {}

    Texture(std::span<const u8> data);
    Texture(const std::filesystem::path& path);

    Texture(const Texture& other); // TODO
    Texture(Texture&& other);      // TODO

    Texture& operator=(const Texture& other); // TODO
    Texture& operator=(Texture&& other);      // TODO

    void set_data(std::span<const u8> data);
    void set_data(std::vector<u8>&& data);

    bool load_from_file(const std::filesystem::path& path);
    bool save_to_file(const std::filesystem::path& path);

    inline auto& data() const { return _data; }
    inline auto width() const { return _width; }
    inline auto height() const { return _height; }

private:
    std::vector<u8> _data;
    u32 _width;
    u32 _height;
};

} // namespace zth
