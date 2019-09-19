#include "Engine.h"

class DemoLayer final : public vega::Layer {
public:
  void OnUpdate(const vega::Timestep &ts) override {
    Layer::OnUpdate(ts);
  }
  void OnImGUI(const vega::Timestep &ts) override {
    Layer::OnImGUI(ts);
  }
  void OnEvent(const vega::Event &ev) override {
    Layer::OnEvent(ev);
  }
};

class Sandbox final : public vega::Application {
public:
  Sandbox() : Application(800, 800, "Vega", 16) {
    PushLayer(new DemoLayer());
  }
};

vega::Application *vega::Make() { return new Sandbox(); }