#pragma once

#include <Vega/Std.hpp>

#include <Vega/Core/Config.hpp>

namespace Vega::Core::Loader {
  class ConfigLoader final {
  public:
    explicit ConfigLoader(boost::filesystem::path root) : mRoot(root) {
      VEGA_RUNTIME_ERROR(!boost::filesystem::is_directory(mRoot), "Invalid sketch path")
    }

  public:
    void Update() {
      mConfigs.erase(std::remove_if(std::begin(mConfigs), std::end(mConfigs), [](const Config &config) {
        return !config.Exists() || config.HasChanged();
      }), std::end(mConfigs));

      for (const auto &path : boost::filesystem::recursive_directory_iterator(mRoot))
        if (boost::filesystem::is_regular_file(path))
          if (path.path().extension() == ".yml" || path.path().extension() == ".yaml")
            if (std::find(std::begin(mConfigs), std::end(mConfigs), path) == std::end(mConfigs))
              mConfigs.emplace_back(path);
    }

  private:
    boost::filesystem::path mRoot;

    std::vector<Config> mConfigs;
  };
}