#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#pragma once

#include <Std.hpp>

#include <Core/Core.hpp>

namespace Vega::Utility {
  class Settings final {
    using Variant = std::variant<bool, int, float, std::string>;

  VEGA_SINGLETON(Settings)

  private:
    explicit Settings() = default;

  public:
    inline void Set(const std::string &key, const Variant &v) { mVariables.insert({key, v}); }

    template<typename T>
    inline T Get(const std::string &key) const {
      auto it = mVariables.find(key);

      if (it == std::end(mVariables)) return T{};
      else return std::get<T>(it->second);
    }

  private:
    std::map<const std::string, const Variant> mVariables;
  };
}

#endif