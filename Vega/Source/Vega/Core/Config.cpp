#include <Vega/Core/Config.hpp>

Vega::Core::Config::Config(const boost::filesystem::path &file) :
    mFile({file, boost::filesystem::last_write_time(file)}) {
  const YAML::Node config = YAML::LoadFile(file.string().c_str());

  if (!Validate(config)) return;

  const std::string name = config["name"].as<std::string>();
  const boost::filesystem::path outputPath = config["output-path"].as<std::string>();
  const std::vector<std::string> watchList = config["watch-list"].as<std::vector<std::string>>();

  const boost::filesystem::path output = outputPath / name;

  for (const auto &item : watchList) {
    boost::filesystem::path subFile = mFile.first.parent_path() / item;
    mFiles.insert({subFile, boost::filesystem::last_write_time(subFile)});
  }

  switch (config["type"].as<ConfigType>().Type) {
    case Identifier::Plugin: {
      const std::string main = config["main"].as<std::string>();
      const boost::filesystem::path input = outputPath / main;

      if (!Compiler::Cpp(input, output, true))
        VEGA_ERROR("Failed to compile plugin: %s", name.c_str())
      else
        VEGA_INFO("Successfully compiled plugin: %s", name.c_str())

      break;
    }
    case Identifier::Shader: {
      std::vector<boost::filesystem::path> files;

      for (const auto &item : watchList) files.emplace_back(mFile.first.parent_path() / item);

      if (!Compiler::Glsl(files, output, true))
        VEGA_ERROR("Failed to compile shader: %s", name.c_str())
      else
        VEGA_INFO("Successfully compiled shader: %s", name.c_str())

      break;
    }
    default:
      break;
  }
}

bool Vega::Core::Config::HasChanged() const {
  if (boost::filesystem::last_write_time(mFile.first) > mFile.second) return true;

  for (const auto &[subFile, prevTime] : mFiles)
    if (boost::filesystem::last_write_time(subFile) > prevTime) return true;

  return false;
}

bool Vega::Core::Config::Validate(const YAML::Node &config) const {
  if (!config["type"] || !config["type"].IsScalar()) {
    VEGA_ERROR("Config key (%s) is missing or has wrong type", "type")
    return false;
  }

  if (!config["name"] || !config["name"].IsScalar()) {
    VEGA_ERROR("Config key (%s) is missing or has wrong type", "name")
    return false;
  }

  if (!config["output-path"] || !config["output-path"].IsScalar()) {
    VEGA_ERROR("Config key (%s) is missing or has wrong type", "output-path")
    return false;
  } else {
    if (!boost::filesystem::is_directory(config["output-path"].as<std::string>())) {
      VEGA_ERROR("Config key (%s) is is not a directory", "output-path")
      return false;
    }
  }

  ConfigType type = config["type"].as<ConfigType>();

  switch (type.Type) {
    case Identifier::Plugin: {
      if (!config["main"] || !config["main"].IsScalar()) {
        VEGA_ERROR("Config key (%s) is missing or has wrong type", "main")
        return false;
      }

      break;
    }
    case Identifier::Shader: {
      break;
    }
    default: {
      VEGA_ERROR("Config key (%s) has wrong identifier", "type")
      return false;
    }
  }

  if (!config["watch-list"] || !config["watch-list"].IsSequence()) {
    VEGA_ERROR("Config key (%s) is missing or has wrong type", "watch-list")
    return false;
  } else {
    for (const auto &item : config["watch-list"].as<std::vector<std::string>>()) {
      boost::filesystem::path subFile = mFile.first.parent_path() / item;

      if (!boost::filesystem::is_regular_file(subFile)) {
        VEGA_ERROR("Config key (%s:%s) is not a file", "watch-list", subFile.c_str())
        return false;
      }
    }
  }

  return true;
}
