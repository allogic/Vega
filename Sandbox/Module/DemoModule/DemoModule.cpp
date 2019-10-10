#include <iostream>

#include <Vega/Core/Module.hpp>

class DemoModule final : public Vega::Core::Module {
public:
  void OnUpdate(float deltaTime) override {

  }
};

extern "C" Vega::Core::Module *Create() { return new DemoModule(); }