#pragma once

#include <Vega/Std.hpp>

#include <Vega/Core/Core.hpp>
#include <Vega/Core/SharedObject.hpp>

namespace Vega::Core::Loader {
  class PluginLoader final {
  public:
    explicit PluginLoader(boost::filesystem::path root) : mRoot(root) {
      VEGA_RUNTIME_ERROR(!boost::filesystem::is_directory(mRoot), "Invalid sketch path")
    }

    void Update() {
      mSharedObjects.erase(
          std::remove_if(std::begin(mSharedObjects), std::end(mSharedObjects), [](const SharedObject &obj) {
            return !obj.Exists() || obj.HasChanged();
          }), std::end(mSharedObjects));
    }

  private:
    boost::filesystem::path mRoot;

    std::vector<SharedObject> mSharedObjects;
  };
}