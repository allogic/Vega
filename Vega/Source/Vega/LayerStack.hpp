#ifndef VEGA_LAYERSTACK_HPP
#define VEGA_LAYERSTACK_HPP

#include <vector>
#include <algorithm>

#include <Vega/Layer.hpp>

namespace Vega {
  class LayerStack final {
  public:
    LayerStack() = default;

    virtual ~LayerStack() {
      for (auto layer : mLayers) delete layer;
    }

    void Push(Layer *layer) {
      mLayers.emplace(std::begin(mLayers) + mInsertIndex, layer);

      mInsertIndex++;

      layer->OnAttach();
    }

    void Pop(Layer *layer) {
      auto it = std::find(std::begin(mLayers), std::end(mLayers) + mInsertIndex, layer);

      if (it != std::begin(mLayers) + mInsertIndex) {
        layer->OnDetach();

        mLayers.erase(it);

        mInsertIndex--;
      }
    }

    std::vector<Layer *>::iterator begin() { return std::begin(mLayers); }
    std::vector<Layer *>::iterator end() { return std::end(mLayers); }

  private:
    std::vector<Layer *> mLayers;

    unsigned int mInsertIndex = 0;
  };
}

#endif