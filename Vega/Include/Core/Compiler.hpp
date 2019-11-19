#ifndef COMPILER_HPP
#define COMPILER_HPP

#pragma once

#include <Std.hpp>
#include <Platform.hpp>

#include <Core/Core.hpp>

#include <Utility/Settings.hpp>
#include <Utility/Io.hpp>

namespace Vega::Core {
  class Compiler final {
  public:
    static bool Cpp(const std::experimental::filesystem::path &input,
                    const std::experimental::filesystem::path &output,
                    bool verbose);

    static bool Glsl(const std::vector<std::experimental::filesystem::path> &files,
                     const std::experimental::filesystem::path &outputFile,
                     bool verbose = false);
  };
}

#endif