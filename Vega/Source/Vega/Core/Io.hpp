#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>

#include <Vega/Core/Core.hpp>

namespace Vega::Io {
  static bool Read(std::string &data, const std::filesystem::path &path) {
    VEGA_RUNTIME_ERROR(!std::filesystem::exists(path) || std::filesystem::is_directory(path), "Invalid path");

    std::ifstream file(path);

    std::stringstream ss;
    std::string line;

    if (!file.is_open()) return false;

    while (getline(file, line))
      ss << line << std::endl;

    file.close();

    data = ss.str();

    return true;
  }

  static bool Write(const std::string &data, const std::filesystem::path &path) {
    VEGA_RUNTIME_ERROR(!std::filesystem::exists(path) || std::filesystem::is_directory(path), "Invalid path");

    std::ofstream file(path);

    if (!file.is_open()) return false;

    file << data;

    file.close();

    return true;
  }
}