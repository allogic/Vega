#include "engine.h"

using namespace vega;

class Sandbox final : public Application {
public:
  Sandbox() : Application(800, 800, "Vega", 16) {}
};

Application *vega::make() { return new Sandbox(); }