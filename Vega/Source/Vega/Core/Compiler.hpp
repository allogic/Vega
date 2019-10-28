#pragma once

#include <Vega/Std.hpp>
#include <Vega/Platform.hpp>

#include <Vega/Core/Core.hpp>

#include <Vega/Utility/Settings.hpp>
#include <Vega/Utility/Io.hpp>

namespace Vega::Core {
  namespace fs = std::experimental::filesystem;

  class Compiler final {
  public:
    static bool CompilePlugin(const std::string &name,
                              const std::vector<fs::path> &files,
                              const std::string &outputFile,
                              bool verbose = false);

    static bool CompileShader(const std::string &name,
                              const std::vector<fs::path> &files,
                              const std::string &outputFile,
                              bool verbose = false);
  };
}