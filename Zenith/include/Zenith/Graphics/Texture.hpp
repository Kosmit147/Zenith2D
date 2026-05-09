/**
 * @file Texture.hpp
 * @brief Defines the `Texture` class for loading and handling textures in a graphics system.
 * 
 * This file provides the interface for loading textures from files or memory, binding them for rendering, 
 * and querying their size. It also includes a `TextureSize` struct to store the dimensions of a texture.
 */

#pragma once

#include <SFML/Graphics/Texture.hpp>

#include <optional>
#include <span>
#include <string_view>

#include "Zenith/Core/Typedefs.hpp"
#include "Zenith/Utility/Utility.hpp"

namespace zth {

/**
 * @struct TextureSize
 * @brief Represents the dimensions of a texture (width and height).
 */
struct TextureSize
{
    u32 width; ///< The width of the texture in pixels.
    u32 height; ///< The height of the texture in pixels.
};

/**
 * @class Texture
 * @brief A texture class for loading, binding, and accessing texture data.
 * 
 * This class provides methods to load textures from files or memory, bind them for rendering, 
 * and query their size. The texture must remain valid for as long as it is used in rendering.
 */
class Texture
{
public:
    /**
     * @brief Default constructor for `Texture`.
     * 
     * Creates an empty texture.
     */
    explicit Texture() = default;

    /**
     * @brief Constructs a `Texture` from a given size.
     * @param size The dimensions of the texture.
     */
    explicit Texture(TextureSize size);

    /**
     * @brief Loads a texture from a file.
     * @param path The path to the texture file.
     * @return A `std::optional<Texture>` containing the loaded texture if successful, or empty if failed.
     */
    static std::optional<Texture> from_file(std::string_view path);

    /**
     * @brief Loads a texture from memory (with a specified size).
     * @tparam DataSize The size of the data in bytes.
     * @param data The raw data for the texture.
     * @return A `std::optional<Texture>` containing the loaded texture if successful, or empty if failed.
     */
    template<usize DataSize> static std::optional<Texture> from_memory(std::span<const u8, DataSize> data);

    /**
     * @brief Loads a texture from memory.
     * @param data The raw data for the texture.
     * @param data_size The size of the data in bytes.
     * @return A `std::optional<Texture>` containing the loaded texture if successful, or empty if failed.
     */
    static std::optional<Texture> from_memory(const u8* data, usize data_size);

    /**
     * @brief Default copy constructor (deleted).
     * 
     * A texture cannot be copied due to SFML's texture management restrictions.
     */
    ZTH_DEFAULT_COPY(Texture)

    /**
     * @brief Destructor for `Texture`.
     */
    ~Texture() = default;

    /**
     * @brief Move constructor for `Texture`.
     * @param other The texture to move.
     */
    Texture(Texture&& other) noexcept;

    /**
     * @brief Move assignment operator for `Texture`.
     * @param other The texture to move.
     * @return A reference to this texture.
     */
    Texture& operator=(Texture&& other) noexcept;

    /**
     * @brief Loads a texture from a file.
     * @param path The path to the texture file.
     * @return `true` if successful, `false` otherwise.
     */
    bool load_from_file(std::string_view path);

    /**
     * @brief Loads a texture from memory.
     * @param data The raw data for the texture.
     * @param data_size The size of the data in bytes.
     * @return `true` if successful, `false` otherwise.
     */
    bool load_from_memory(const u8* data, usize data_size);

    /**
     * @brief Gets the width of the texture.
     * @return The width of the texture in pixels.
     */
    auto width() const { return _texture.getSize().x; }

    /**
     * @brief Gets the height of the texture.
     * @return The height of the texture in pixels.
     */
    auto height() const { return _texture.getSize().y; }

    /**
     * @brief Gets the size of the texture.
     * @return A `TextureSize` struct containing the width and height of the texture.
     */
    auto size() const { return TextureSize{ width(), height() }; }

    /**
     * @brief Binds the texture for rendering.
     * 
     * This makes the texture the current active texture for the OpenGL context.
     */
    void bind() const { sf::Texture::bind(&_texture); }

    /**
     * @brief Unbinds any currently bound texture.
     * 
     * This unbinds the texture from the OpenGL context.
     */
    static void unbind() { sf::Texture::bind(nullptr); }

    /**
     * @brief Gets the native OpenGL handle for the texture.
     * @return The native OpenGL handle for the texture.
     */
    unsigned int get_native_handle() const { return _texture.getNativeHandle(); }

    friend class Shader;
    friend class Sprite;

private:
    sf::Texture _texture; ///< The underlying SFML texture object.
};

/**
 * @brief Loads a texture from memory (with a specified size).
 * @tparam DataSize The size of the data in bytes.
 * @param data The raw data for the texture.
 * @return A `std::optional<Texture>` containing the loaded texture if successful, or empty if failed.
 */
template<usize DataSize> std::optional<Texture> Texture::from_memory(std::span<const u8, DataSize> data)
{
    return std::optional{ Texture::from_memory(data.data(), data.size_bytes()) };
}

} // namespace zth
