#pragma once

#include <fstream>
#include <filesystem>
#include <sstream>
#include <string_view>

// TODO: move to cpp file
inline std::optional<std::stringstream> read_from_file(const std::filesystem::path& path)
{
    if (!std::filesystem::exists(path)) [[unlikely]]
        return {};

    std::ifstream file(path);
    std::stringstream stream;

    auto file_buf = file.rdbuf();

    if (!file_buf) [[unlikely]]
        return {};

    stream << file_buf << '\0';

    if (!stream.good()) [[unlikely]]
        return {};

    return std::optional<std::stringstream>{ stream };
}

// TODO: move to cpp file
inline bool write_to_file(const std::filesystem::path& path, std::string_view content)
{
    if (!std::filesystem::exists(path)) [[unlikely]]
        return false;

    std::ofstream file(path);
    file << content.data();

    if (!file.good())
        return false;

    return true;
}
