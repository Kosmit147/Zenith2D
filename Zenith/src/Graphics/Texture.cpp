#include "Zenith/Graphics/Texture.hpp"

namespace zth {

Texture::Texture(TextureSize size)
{
    _texture.create(size.width, size.height);
}

std::optional<Texture> Texture::from_file(std::string_view path)
{
    if (Texture tex; tex.load_from_file(path))
        return std::optional{ tex };

    return {};
}

std::optional<Texture> Texture::from_memory(const u8* data, usize data_size)
{
    if (Texture tex; tex.load_from_memory(data, data_size))
        return std::optional{ tex };

    return {};
}

Texture::Texture(Texture&& other) noexcept
{
    _texture.swap(other._texture);
}

Texture& Texture::operator=(Texture&& other) noexcept
{
    _texture.swap(other._texture);
    return *this;
}

bool Texture::load_from_file(std::string_view path)
{
    return _texture.loadFromFile(path.data());
}

bool Texture::load_from_memory(const u8* data, usize data_size)
{
    return _texture.loadFromMemory(data, data_size);
}

} // namespace zth
