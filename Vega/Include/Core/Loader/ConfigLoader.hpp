#ifndef CONFIGLOADER_HPP
#define CONFIGLOADER_HPP

#pragma once

#include <Std.hpp>

#include <Core/Config.hpp>

#include <Utility/Settings.hpp>

namespace Vega::Core::Loader {
  class ConfigLoader final {
  public:
    explicit ConfigLoader() {
      auto &settings = Vega::Utility::Settings::Instance();

      mRoot = settings.Get<std::string>("sketch-path");

      //VEGA_RUNTIME_ERROR(!std::experimental::filesystem::is_directory(mRoot), "Invalid sketch path")
    }

  public:
    void Update() {
      mConfigs.erase(std::remove_if(std::begin(mConfigs), std::end(mConfigs), [](const Config &config) {
        return !config.Exists() || config.HasChanged();
      }), std::end(mConfigs));

      for (const auto &path : std::experimental::filesystem::recursive_directory_iterator(mRoot))
        if (std::experimental::filesystem::is_regular_file(path))
          if (path.path().extension() == ".yml" || path.path().extension() == ".yaml")
            if (std::find(std::begin(mConfigs), std::end(mConfigs), path) == std::end(mConfigs))
              mConfigs.emplace_back(path);
    }

  private:
    std::experimental::filesystem::path mRoot;

    std::vector<Config> mConfigs;
  };
}

#endif