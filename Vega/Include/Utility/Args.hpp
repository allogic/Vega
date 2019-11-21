#ifndef ARGS_HPP
#define ARGS_HPP

#pragma once

#include <Std.hpp>

#include <cxxopts.hpp>

#include <Utility/Settings.hpp>

namespace Vega::Utility::Args {
  template<typename T>
  static void FindKeyOrSetError(const cxxopts::ParseResult &args, const std::string &key, bool &error) {
    if (args.count(key) == 1)
      Vega::Utility::Settings::Instance().Set(key, args[key].as<T>());
    else {
      VEGA_INFO("Missing or too many arguments {0}", key)
      error = true;
    }
  }

  static bool Handle(int argc, char **argv) {
    cxxopts::Options options{"Vega", "Vega Engine"};

    options.add_option("", "", "width", "Window width", cxxopts::value<int>(), "");
    options.add_option("", "", "height", "Window height", cxxopts::value<int>(), "");
    options.add_option("", "", "title", "Window title", cxxopts::value<std::string>(), "");
    options.add_option("", "", "gl-major", "OpenGL major version", cxxopts::value<int>(), "");
    options.add_option("", "", "gl-minor", "OpenGL minor version", cxxopts::value<int>(), "");
    options.add_option("", "", "glsl-version", "GLSL version", cxxopts::value<int>(), "");
    options.add_option("", "", "antialiasing", "Antialiasing", cxxopts::value<int>(), "");
    options.add_option("", "", "sketch-path", "Sketch path", cxxopts::value<std::string>(), "");
    options.add_option("", "", "cpp-compiler", "C++ compiler path", cxxopts::value<std::string>(), "");
    options.add_option("", "", "vega-include-path", "Vega API path", cxxopts::value<std::string>(), "");

    auto args = options.parse(argc, argv);

    bool error = false;

    FindKeyOrSetError<int>(args, "width", error);
    FindKeyOrSetError<int>(args, "height", error);
    FindKeyOrSetError<std::string>(args, "title", error);
    FindKeyOrSetError<int>(args, "gl-major", error);
    FindKeyOrSetError<int>(args, "gl-minor", error);
    FindKeyOrSetError<int>(args, "glsl-version", error);
    FindKeyOrSetError<int>(args, "antialiasing", error);
    FindKeyOrSetError<std::string>(args, "sketch-path", error);
    FindKeyOrSetError<std::string>(args, "cpp-compiler", error);
    FindKeyOrSetError<std::string>(args, "vega-include-path", error);

    return !error;
  }
}

#endif