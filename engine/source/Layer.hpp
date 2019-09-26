#ifndef VEGA_LAYER_HPP
#define VEGA_LAYER_HPP

namespace Vega {
  class VEGA_API Layer {
  public:
    explicit Layer() = default;

    virtual ~Layer() = default;

    virtual void OnUpdate(double dt) {}
    virtual void OnDraw() {}
    virtual void OnImgui(double dt) {}
  };
}

#endif