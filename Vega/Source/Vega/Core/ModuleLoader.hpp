#pragma once

#include <Vega/Std.hpp>
#include <Vega/Platform.hpp>

#include <Vega/Core/Core.hpp>
#include <Vega/Core/Filesystem.hpp>
#include <Vega/Core/SharedObject.hpp>

#include <Vega/Debug/Core.hpp>

namespace Vega::Core {
  class ModuleLoader final {
  VEGA_SINGLETON(ModuleLoader)

  public:
    void DebugReloadIfChanged();

    void OnUpdate(float deltaTime);

  private:
    explicit ModuleLoader() = default;

    explicit ModuleLoader(const std::filesystem::path &root);

  private:
    std::vector<std::unique_ptr<SharedObject>> mSharedObjects;
  };
}