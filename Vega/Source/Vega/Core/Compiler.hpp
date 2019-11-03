#pragma once

#include <Vega/Std.hpp>
#include <Vega/Platform.hpp>

#include <Vega/Core/Core.hpp>

#include <Vega/Utility/Settings.hpp>
#include <Vega/Utility/Io.hpp>

namespace Vega::Core {
  class Compiler final {
  public:
    static bool Cpp(const boost::filesystem::path &input,
                    const boost::filesystem::path &output,
                    bool verbose);

    static bool Glsl(const std::vector<boost::filesystem::path> &files,
                     const boost::filesystem::path &outputFile,
                     bool verbose = false);
  };
}