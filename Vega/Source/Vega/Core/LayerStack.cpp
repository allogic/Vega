#include <Vega/Core/LayerStack.hpp>

Vega::LayerStack::~LayerStack() {
  for (auto layer : mLayers) delete layer;
}

void Vega::LayerStack::Push(Vega::Layer *layer) {
  mLayers.emplace(std::begin(mLayers) + mInsertIndex, layer);

  mInsertIndex++;

  layer->OnEnable();
}

void Vega::LayerStack::Pop(Vega::Layer *layer) {
  auto it = std::find(std::begin(mLayers), std::end(mLayers) + mInsertIndex, layer);

  if (it != std::begin(mLayers) + mInsertIndex) {
    layer->OnDisable();

    mLayers.erase(it);

    mInsertIndex--;
  }
}