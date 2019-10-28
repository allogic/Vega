#include <iostream>

#include <Vega/Core/Module.hpp>

#include "Test.hpp"

class DemoModule final : public Vega::Core::Module {
public:
  void OnUpdate(float deltaTime) override {
    std::cout << foo() << std::endl;
  }

  void OnDraw() const override {

  }

  void OnEvent(const Vega::Event::Event &event) override {

  }

  void OnGui() override {

  }
};

extern "C" Vega::Core::Module *Create() { return new DemoModule(); }