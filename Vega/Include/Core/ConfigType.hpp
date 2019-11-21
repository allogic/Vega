#ifndef CONFIGTYPE_HPP
#define CONFIGTYPE_HPP

#pragma once

#include <yaml-cpp/yaml.h>

namespace Vega::Core {
  enum class ConfigIdentifier : int {
    None = 0,
    Plugin,
    Shader,
  };

  struct ConfigType {
    ConfigIdentifier Type = ConfigIdentifier::None;
  };
}

namespace YAML {
  template<>
  struct convert<Vega::Core::ConfigType> {
    static bool decode(const Node &node, Vega::Core::ConfigType &type) {
      if (!node.IsScalar()) return false;

      std::string value = node.as<std::string>();

      if (value == "Plugin") type.Type = Vega::Core::ConfigIdentifier::Plugin;
      else if (value == "Shader") type.Type = Vega::Core::ConfigIdentifier::Shader;
      else type.Type = Vega::Core::ConfigIdentifier::None;

      return true;
    }
  };
}

#endif