#include <Vega.hpp>

class Sandbox final : public Vega::Application {
public:
  void OnUpdate() override {

  }

  void OnDraw() const override {

  }

  void OnEvent(const Vega::Event &event) override {
    Application::OnEvent(event);
  }

  void OnGui() override {

  }
};

Vega::Application *Vega::Make() { return new Sandbox(); }