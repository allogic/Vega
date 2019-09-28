#ifndef VEGA_LAYER_HPP
#define VEGA_LAYER_HPP

#include <Vega/Event/Event.hpp>

namespace Vega {
  class Layer {
  public:
    explicit Layer() = default;

    virtual ~Layer() = default;

    virtual void OnAttach();
    virtual void OnDetach();

    virtual void OnUpdate(double deltaTime);
    virtual void OnDraw();
    virtual void OnImGui(double deltaTime);
    virtual void OnEvent(Event &event);
  };
}

#endif