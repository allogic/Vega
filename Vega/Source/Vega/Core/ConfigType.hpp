#pragma once

#include <Vega/Vendor/Yaml.hpp>

namespace Vega::Core {
  enum class Identifier {
    None,
    Plugin,
    Shader,
  };

  struct ConfigType {
    Identifier Type = Identifier::None;
  };
}

namespace YAML {
  template<>
  struct convert<Vega::Core::ConfigType> {
    static bool decode(const Node &node, Vega::Core::ConfigType &type) {
      if (!node.IsScalar()) return false;

      std::string value = node.as<std::string>();

      if (value == "plugin") type.Type = Vega::Core::Identifier::Plugin;
      else if (value == "shader") type.Type = Vega::Core::Identifier::Shader;
      else type.Type = Vega::Core::Identifier::None;

      return true;
    }
  };
}