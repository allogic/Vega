#ifndef IO_HPP
#define IO_HPP

#pragma once

#include <Std.hpp>

#include <Core/Core.hpp>

namespace Vega::Utility::Io {
  static bool Read(std::string &data, const std::experimental::filesystem::path &file) {
    std::ifstream stream(file.string(), std::ios_base::in);

    std::stringstream ss;
    std::string line;

    if (!stream.good()) {
      stream.close();

      return false;
    }

    while (std::getline(stream, line))
      ss << line << '\n';

    stream.close();

    data = ss.str();

    return true;
  }

  static bool Write(const std::string &data, const std::experimental::filesystem::path &file) {
    std::ofstream stream(file.string(), std::ios_base::out);

    if (!stream.good()) {
      stream.close();

      return false;
    }

    stream << data;

    stream.close();

    return true;
  }
}

#endif