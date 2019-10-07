#pragma once

#include <Vega/Event/Event.hpp>

namespace Vega {
  class MousePositionEvent final : public Event {
  public:
    float X;
    float Y;

    explicit MousePositionEvent(float x, float y) : X(x), Y(y) {}
  };

  class MouseButtonEvent final : public Event {
  public:
    unsigned int Key;

    explicit MouseButtonEvent(unsigned int key) : Key(key) {}
  };

  class MouseScrollEvent final : public Event {
  public:
    float X;
    float Y;

    explicit MouseScrollEvent(float x, float y) : X(x), Y(y) {}
  };
}