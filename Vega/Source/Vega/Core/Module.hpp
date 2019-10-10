#pragma once

namespace Vega::Core {
  class Module {
  public:
    virtual void OnUpdate(float deltaTime) = 0;

  public:
    explicit Module() = default;
    virtual ~Module() = default;
  };
}