#pragma once

namespace Vega {
  class Layer {
  public:
    explicit Layer() = default;

    virtual ~Layer() = default;

    virtual void OnEnable() {}
    virtual void OnDisable() {}

    virtual void OnUpdate(float deltaTime) {}
    virtual void OnDraw() {}
    virtual void OnImGui() {}
  };
}