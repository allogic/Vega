#ifndef LOADER_HPP
#define LOADER_HPP

#pragma once

#include <Std.hpp>

#include <Core/Core.hpp>

namespace Vega::Core::Loader {
  template<class U, bool RemovePred, bool InsertPred>
  class Loader final {
  public:
    explicit Loader(std::experimental::filesystem::path &root) : mRoot(root) {
      VEGA_ASSERT(std::experimental::filesystem::is_directory(mRoot), "Invalid loader path")
    }

    void Update(RemovePred &&removePred, InsertPred &&insertPred) {
      mObjects.erase(std::remove_if(std::begin(mObjects), std::end(mObjects), removePred), std::end(mObjects));


    }

  private:
    std::experimental::filesystem::path mRoot;

    std::vector<U> mObjects;
  };
}

#endif