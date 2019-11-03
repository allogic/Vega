#pragma once

#include <Vega/Std.hpp>

#include <Vega/Core/Core.hpp>

namespace Vega::Core::Loader {
  template<class U, bool RemovePred, bool InsertPred>
  class Loader final {
  public:
    explicit Loader(boost::filesystem::path &root) : mRoot(root) {
      VEGA_RUNTIME_ERROR(!boost::filesystem::is_directory(mRoot), "Invalid loader path")
    }

    void Update(RemovePred &&removePred, InsertPred &&insertPred) {
      mObjects.erase(std::remove_if(std::begin(mObjects), std::end(mObjects), removePred), std::end(mObjects));


    }

  private:
    boost::filesystem::path mRoot;

    std::vector<U> mObjects;
  };
}