#include <Core/Config.hpp>

Vega::Core::Config::Config(const std::experimental::filesystem::path &file) :
    mFile({file, std::experimental::filesystem::last_write_time(file)}) {
  const YAML::Node config = YAML::LoadFile(file.string().c_str());

  if (!Validate(config)) return;

  const std::string name = config["name"].as<std::string>();
  const std::experimental::filesystem::path outputPath = config["output-path"].as<std::string>();
  const std::vector<std::string> watchList = config["watch-list"].as<std::vector<std::string>>();

  const std::experimental::filesystem::path output = outputPath / name;

  for (const auto &item : watchList) {
    std::experimental::filesystem::path subFile = mFile.first.parent_path() / item;
    mFiles.insert({subFile, std::experimental::filesystem::last_write_time(subFile)});
  }

  switch (config["type"].as<ConfigType>().Type) {
    case ConfigIdentifier::Plugin: {
      const std::string main = config["main"].as<std::string>();
      const std::experimental::filesystem::path input = outputPath / main;

      if (Compiler::Cpp(input, output, true)) {
        //VEGA_INFO("Successfully compiled plugin: ", name.c_str())
      } else {
        //VEGA_ERROR("Failed to compile plugin: ", name.c_str())
      }

      break;
    }
    case ConfigIdentifier::Shader: {
      std::vector<std::experimental::filesystem::path> files;

      for (const auto &item : watchList) files.emplace_back(mFile.first.parent_path() / item);

      if (Compiler::Glsl(files, output, true)) {
        //VEGA_INFO("Successfully compiled shader: ", name.c_str())
      } else {
        //VEGA_ERROR("Failed to compile shader: ", name.c_str())
      }

      break;
    }
    default:break;
  }
}

bool Vega::Core::Config::HasChanged() const {
  if (std::experimental::filesystem::last_write_time(mFile.first) > mFile.second) return true;

  for (const auto &[subFile, prevTime] : mFiles)
    if (std::experimental::filesystem::last_write_time(subFile) > prevTime) return true;

  return false;
}

bool Vega::Core::Config::Validate(const YAML::Node &config) const {
  if (!config["type"] || !config["type"].IsScalar()) {
    VEGA_ERROR("Config key type is missing or has wrong type")
    return false;
  }

  if (!config["name"] || !config["name"].IsScalar()) {
    VEGA_ERROR("Config key name is missing or has wrong type")
    return false;
  }

  if (!config["output-path"] || !config["output-path"].IsScalar()) {
    VEGA_ERROR("Config key output-path is missing or has wrong type")
    return false;
  } else {
    if (!std::experimental::filesystem::is_directory(config["output-path"].as<std::string>())) {
      VEGA_ERROR("Config key output-path is is not a directory")
      return false;
    }
  }

  ConfigType type = config["type"].as<ConfigType>();

  switch (type.Type) {
    case ConfigIdentifier::Plugin: {
      if (!config["main"] || !config["main"].IsScalar()) {
        VEGA_ERROR("Config key main is missing or has wrong type")
        return false;
      }

      break;
    }
    case ConfigIdentifier::Shader: {
      break;
    }
    default: {
      VEGA_ERROR("Config key type has wrong identifier")
      return false;
    }
  }

  if (!config["watch-list"] || !config["watch-list"].IsSequence()) {
    VEGA_ERROR("Config key watch-list is missing or has wrong type")
    return false;
  } else {
    for (const auto &item : config["watch-list"].as<std::vector<std::string>>()) {
      std::experimental::filesystem::path subFile = mFile.first.parent_path() / item;

      if (!std::experimental::filesystem::is_regular_file(subFile)) {
        //VEGA_ERROR("Config key watch-list is not a file") //TODO fix me
        return false;
      }
    }
  }

  return true;
}
