#pragma once

#include <Vega/Std.hpp>

#include <Vega/Vendor/Yaml.hpp>

#include <Vega/Core/Compiler.hpp>

namespace Vega::Core {
  namespace fs = std::experimental::filesystem;

  using TimePoint = std::chrono::system_clock::time_point;

  class Config final {
    friend class ConfigLoader;

  public:
    Config(const fs::path &file) : mFile({file, fs::last_write_time(file)}) {
      const YAML::Node node = YAML::LoadFile(file);

      if (!node["name"]) {
        VEGA_ERROR("Config key (%s) is required", "name")
        return;
      }

      if (!node["type"]) {
        VEGA_ERROR("Config key (%s) is required", "type")
        return;
      }

      if (!node["output-path"]) {
        VEGA_ERROR("Config key (%s) is required", "output-path")
        return;
      }

      if (!node["files"]) {
        VEGA_ERROR("Config key (%s) is required", "files")
        return;
      } else if (node["files"].Type() != YAML::NodeType::Sequence) {
        VEGA_ERROR("Config key (%s) is not a sequence", "files")
        return;
      }

      const std::string name = node["name"].as<std::string>();
      const std::string type = node["type"].as<std::string>();
      const fs::path outputPath = node["output-path"].as<std::string>();
      const std::vector<std::string> files = node["files"].as<std::vector<std::string>>();

      if (!fs::is_directory(outputPath))
        VEGA_ERROR("Path does not exist %s", outputPath.c_str())

      std::vector<fs::path> validFiles;

      bool error = false;

      for (const auto &item : files) {
        fs::path subFile = mFile.first.parent_path() / item;

        if (!fs::is_regular_file(subFile)) {
          VEGA_ERROR("File does not exist %s", subFile.c_str())

          error = true;

          continue;
        }

        validFiles.emplace_back(subFile.string());

        mFiles.insert({subFile, fs::last_write_time(subFile)});
      }

      if (error) return;

      if (type == "plugin") {
        if (Compiler::CompilePlugin(name, validFiles, outputPath / name, true))
          VEGA_ERROR("Failed to compile plugin: %s", name.c_str())
      } else if (type == "shader") {
        //Compiler::CompileShader(name, validFiles, outputPath / name, true);
      } else {
        VEGA_ERROR("Config type (%s) is not supported", type.c_str())
      }
    }

  public:
    auto operator==(const fs::path &file) const { return mFile.first == file; }

  public:
    bool HasChanged() const {
      if (fs::last_write_time(mFile.first) > mFile.second) return true;

      for (const auto &[subFile, prevTime] : mFiles)
        if (fs::last_write_time(subFile) > prevTime) return true;

      return false;
    }

  private:
    std::pair<fs::path, TimePoint> mFile;
    std::map<fs::path, TimePoint> mFiles;
  };

  class ConfigLoader final {
  public:
    explicit ConfigLoader(fs::path root) : mRoot(root) {
      VEGA_RUNTIME_ERROR(!fs::is_directory(mRoot), "Invalid sketch path " / mRoot)
    }

  public:
    void Update() {
      mConfigs.erase(std::remove_if(std::begin(mConfigs), std::end(mConfigs), [](const Config &config) {
        return !fs::is_regular_file(config.mFile.first) || config.HasChanged();
      }), std::end(mConfigs));

      for (const auto &path : fs::recursive_directory_iterator(mRoot))
        if (fs::is_regular_file(path))
          if (path.path().extension() == ".yml" || path.path().extension() == ".yaml")
            if (std::find(std::begin(mConfigs), std::end(mConfigs), path) == std::end(mConfigs))
              mConfigs.emplace_back(path);
    }

  private:
    fs::path mRoot;

    std::vector<Config> mConfigs;
  };
}