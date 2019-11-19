#ifndef MODULE_HPP
#define MODULE_HPP

#pragma once

#include <Event/Event.hpp>

namespace Vega::Core {
  class Module {
  public:
    explicit Module() = default;
    virtual ~Module() = default;

  public:
    virtual void OnUpdate(float deltaTime) = 0;
    virtual void OnDraw() const = 0;
    virtual void OnEvent(const Event::Event &event) = 0;
    virtual void OnGui() = 0;
  };
}

#endif