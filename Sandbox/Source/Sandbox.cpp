#include <Vega.hpp>

namespace Demo {
  class CustomLayer final : public Vega::Layer {
  public:
    explicit CustomLayer() = default;

    ~CustomLayer() final = default;

    void OnUpdate(double deltaTime) override {}

    void OnDraw() override {}

    void OnImGui(double deltaTime) override {
      ImGui::Text("Demo");
    }

    void OnEvent(Vega::Event &event) override {}
  };

  class Sandbox final : public Vega::Application {
  public:
    Sandbox() : Application() {
      PushLayer(new CustomLayer());
    }
  };
}

Vega::Application *Vega::Make() { return new Demo::Sandbox(); }