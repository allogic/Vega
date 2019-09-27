#ifndef VEGA_CUSTOMLAYER_HPP
#define VEGA_CUSTOMLAYER_HPP

namespace Demo {
  class CustomLayer final : public Vega::Layer {
  public:
    explicit CustomLayer() = default;

    ~CustomLayer() final = default;

    void OnUpdate(double deltaTime) override {

    }

    void OnDraw() override {

    }

    void OnImGui(double deltaTime) override {
      //ImGui::Text("Demo");
    }
  };
}

#endif