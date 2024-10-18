#pragma once

#include <filesystem>
#include <optional>
#include <sstream>
#include <string_view>

std::optional<std::stringstream> read_from_file(const std::filesystem::path& path);
bool write_to_file(const std::filesystem::path& path, std::string_view content);
bool append_to_file(const std::filesystem::path& path, std::string_view content);
bool append_to_file_with_newline(const std::filesystem::path& path, std::string_view content);
