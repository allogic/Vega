#pragma once

#include <vector>
#include <algorithm>

#include <Vega/Core/Layer.hpp>

namespace Vega {
  class LayerStack final {
  public:
    LayerStack() = default;

    virtual ~LayerStack();

    void Push(Layer *layer);
    void Pop(Layer *layer);

    inline std::vector<Layer *>::iterator begin() { return std::begin(mLayers); }
    inline std::vector<Layer *>::iterator end() { return std::end(mLayers); }

  private:
    std::vector<Layer *> mLayers;

    unsigned int mInsertIndex = 0;
  };
}