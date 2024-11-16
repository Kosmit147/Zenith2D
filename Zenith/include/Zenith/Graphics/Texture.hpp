#pragma once

#include <SFML/Graphics/Texture.hpp>

#include <optional>
#include <span>
#include <string_view>

#include "Zenith/Core/Typedefs.hpp"
#include "Zenith/Utility/Utility.hpp"

namespace zth {

struct TextureSize
{
    u32 width;
    u32 height;
};

// The texture needs to live as long as it is used!
class Texture
{
public:
    explicit Texture() = default;
    explicit Texture(TextureSize size);
    static std::optional<Texture> from_file(std::string_view path);
    template<usize DataSize> static std::optional<Texture> from_memory(std::span<const u8, DataSize> data);
    static std::optional<Texture> from_memory(const u8* data, usize data_size);
    ZTH_DEFAULT_COPY(Texture)

    ~Texture() = default;

    Texture(Texture&& other) noexcept;
    Texture& operator=(Texture&& other) noexcept;

    bool load_from_file(std::string_view path);
    bool load_from_memory(const u8* data, usize data_size);

    auto width() const { return _texture.getSize().x; }
    auto height() const { return _texture.getSize().y; }
    auto size() const { return TextureSize{ width(), height() }; }

    void bind() const { sf::Texture::bind(&_texture); }
    static void unbind() { sf::Texture::bind(nullptr); }

    unsigned int get_native_handle() const { return _texture.getNativeHandle(); }

    friend class Shader;
    friend class Sprite;

private:
    sf::Texture _texture;
};

template<usize DataSize> std::optional<Texture> Texture::from_memory(std::span<const u8, DataSize> data)
{
    return std::optional{ Texture::from_memory(data.data(), data.size_bytes()) };
}

} // namespace zth
