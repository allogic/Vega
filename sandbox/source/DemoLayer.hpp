#ifndef VEGA_CUSTOMLAYER_HPP
#define VEGA_CUSTOMLAYER_HPP

namespace Demo {
  class CustomLayer final : public Vega::Layer {
  public:
    explicit CustomLayer() = default;

    ~CustomLayer() final = default;

    void OnUpdate(double dt) override {

    }

    void OnDraw() override {

    }

    void OnImgui(double dt) override {
      ImGui::Text("Demo");
    }
  };
}

#endif