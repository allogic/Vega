#include <Vega.hpp>

class Sandbox final : public Vega::Core::Application {
public:
  void OnUpdate() override {

  }

  void OnDraw() const override {

  }

  void OnEvent(const Vega::Event::Event &event) override {
    Application::OnEvent(event);
  }

  void OnGui() override {

  }
};

extern Vega::Core::Application *Vega::Core::Make() { return new Sandbox(); }