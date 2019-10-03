#include <Vega.hpp>

class DemoLayer final : public Vega::Layer {
public:
  void OnUpdate(float deltaTime) override {

  }

  void OnDraw() override {

  }
};

class Sandbox final : public Vega::Application {
public:
  explicit Sandbox() : Vega::Application() {
    PushLayer(new DemoLayer());
  }
};

Vega::Application *Vega::Make() { return new Sandbox(); }