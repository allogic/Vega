#ifndef VEGA_CUSTOMLAYER_HPP
#define VEGA_CUSTOMLAYER_HPP

#include <Vega/Layer.hpp>
#include <Vega/Vendor.hpp>

namespace Demo {
  class CustomLayer final : public Vega::Layer {
  public:
    explicit CustomLayer() = default;

    ~CustomLayer() final = default;

    void OnUpdate(double deltaTime) override;
    void OnDraw() override;
    void OnImGui(double deltaTime) override;
  };
}

#endif