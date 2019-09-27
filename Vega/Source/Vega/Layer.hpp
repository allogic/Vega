#ifndef VEGA_LAYER_HPP
#define VEGA_LAYER_HPP

namespace Vega {
  class Layer {
  public:
    explicit Layer() = default;

    virtual ~Layer() = default;

    virtual void OnAttach() {}
    virtual void OnDetach() {}

    virtual void OnUpdate(double deltaTime) {}
    virtual void OnDraw() {}
    virtual void OnImGui(double deltaTime) {}
  };
}

#endif