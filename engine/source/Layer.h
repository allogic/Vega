#ifndef LAYER_H
#define LAYER_H

namespace vega {
  class VEGA_API Layer {
  public:
    explicit Layer() = default;

    virtual ~Layer() = default;

    virtual void OnUpdate(const Timestep &ts) {}
    virtual void OnImGUI(const Timestep &ts) {}
    virtual void OnEvent(const Event &ev) {}
  };
}

#endif