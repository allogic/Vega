#include <Engine.hpp>

#include "DemoLayer.hpp"

namespace Demo {
  class Sandbox final : public Vega::Application {
  public:
    Sandbox() : Application(800, 800, "Vega", "430", 4, 3, 16) {
      PushLayer(new Demo::CustomLayer());
    }
  };
}

Vega::Application *Vega::Make() { return new Demo::Sandbox(); }