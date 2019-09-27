#include <Vega.hpp>

#include <Vega/Application.hpp>

#include <Sandbox/DemoLayer.hpp>

namespace Demo {
  class Sandbox final : public Vega::Application {
  public:
    Sandbox() : Application() {
      PushLayer(new CustomLayer());
    }
  };
}

Vega::Application *Vega::Make() { return new Demo::Sandbox(); }