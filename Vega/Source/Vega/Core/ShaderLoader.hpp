#pragma once

#include <Vega/Std.hpp>

#include <Vega/Core/Core.hpp>
#include <Vega/Core/Shader.hpp>

#include <Vega/Debug/Core.hpp>

namespace Vega::Core {
  class ShaderLoader {
  VEGA_SINGLETON(ShaderLoader)

  public:
    void DebugReloadIfChanged();

  private:
    explicit ShaderLoader() = default;

    explicit ShaderLoader(const fs::path &root);

  private:
    std::vector<std::shared_ptr<Shader>> mShaders;
  };
}