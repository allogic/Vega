#ifndef CONFIG_HPP
#define CONFIG_HPP

#pragma once

#include <Std.hpp>

#include <yaml-cpp/yaml.h>

#include <Core/Core.hpp>
#include <Core/Compiler.hpp>
#include <Core/ConfigType.hpp>

namespace Vega::Core {
  class Config final {
  public:
    Config(const std::experimental::filesystem::path &file);

  public:
    auto operator==(const std::experimental::filesystem::path &file) const { return mFile.first == file; }

  public:
    bool Exists() const { return std::experimental::filesystem::is_regular_file(mFile.first); }

    bool HasChanged() const;

  private:
    bool Validate(const YAML::Node &config) const;

  private:
    std::pair<std::experimental::filesystem::path, std::experimental::filesystem::file_time_type> mFile;
    std::map<std::experimental::filesystem::path, std::experimental::filesystem::file_time_type> mFiles;
  };
}

#endif