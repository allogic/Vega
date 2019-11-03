#pragma once

#include <Vega/Std.hpp>

#include <Vega/Vendor/Yaml.hpp>

#include <Vega/Core/Core.hpp>
#include <Vega/Core/Compiler.hpp>
#include <Vega/Core/ConfigType.hpp>

namespace Vega::Core {
  class Config final {
  public:
    Config(const boost::filesystem::path &file);

  public:
    auto operator==(const boost::filesystem::path &file) const { return mFile.first == file; }

  public:
    bool Exists() const { return boost::filesystem::is_regular_file(mFile.first); }

    bool HasChanged() const;

  private:
    bool Validate(const YAML::Node &config) const;

  private:
    std::pair<boost::filesystem::path, std::time_t> mFile;
    std::map<boost::filesystem::path, std::time_t> mFiles;
  };
}