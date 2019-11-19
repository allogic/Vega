#ifndef PLUGINLOADER_HPP
#define PLUGINLOADER_HPP

#pragma once

#include <Std.hpp>

#include <Core/Core.hpp>
#include <Core/SharedObject.hpp>

namespace Vega::Core::Loader {
  class PluginLoader final {
  public:
    explicit PluginLoader(std::experimental::filesystem::path root) : mRoot(root) {
      VEGA_ASSERT(std::experimental::filesystem::is_directory(mRoot), "Invalid sketch path")
    }

    void Update() {
      mSharedObjects.erase(
          std::remove_if(std::begin(mSharedObjects), std::end(mSharedObjects), [](const SharedObject &obj) {
            return !obj.Exists() || obj.HasChanged();
          }), std::end(mSharedObjects));
    }

  private:
    std::experimental::filesystem::path mRoot;

    std::vector<SharedObject> mSharedObjects;
  };
}

#endif