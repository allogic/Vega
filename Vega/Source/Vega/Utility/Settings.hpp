#pragma once

#include <Vega/Std.hpp>

#include <Vega/Core/Core.hpp>

#define CONFIG_SET(NAME, OBJECT) Vega::Utility::Settings::Instance().Set(NAME, OBJECT);
#define CONFIG_GET(TYPE, NAME) Vega::Utility::Settings::Instance().Get<TYPE>(NAME)

namespace Vega::Utility {
  class Settings {
    using Variant = std::variant<int, float, std::string>;
    using Iterator = std::map<std::string, Variant>::iterator;
    using ConstIterator = std::map<std::string, Variant>::const_iterator;

  VEGA_SINGLETON(Settings)

  private:
    explicit Settings() = default;

  public:
    inline void Set(const std::string &name, const Variant &v) { mVariables.insert({name, v}); }

    template<typename T>
    inline T Get(const std::string &name) const { return std::get<T>(mVariables.find(name)->second); }

  public:
    inline Iterator begin() { return std::begin(mVariables); }
    inline Iterator end() { return std::end(mVariables); }

    inline ConstIterator begin() const { return std::begin(mVariables); }
    inline ConstIterator end() const { return std::end(mVariables); }

  private:
    std::map<std::string, Variant> mVariables;
  };
}