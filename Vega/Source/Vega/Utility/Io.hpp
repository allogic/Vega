#pragma once

#include <Vega/Std.hpp>

#include <Vega/Core/Core.hpp>

namespace Vega::Utility::Io {
  namespace fs = std::experimental::filesystem;

  static bool Read(std::string &data, const fs::path &file) {
    std::ifstream stream(file, std::ios_base::in);

    std::stringstream ss;
    std::string line;

    if (!stream.good()) {
      stream.close();

      return false;
    }

    while (getline(stream, line))
      ss << line << '\n';

    stream.close();

    data = ss.str();

    return true;
  }

  static bool Write(const std::string &data, const fs::path &file) {
    std::ofstream stream(file, std::ios_base::out);

    if (!stream.good()) {
      stream.close();

      return false;
    }

    stream << data;

    stream.close();

    return true;
  }
}