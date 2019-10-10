#pragma once

#include <Vega/Event/Event.hpp>

namespace Vega::Event {
  class MousePositionEvent final : public Event {
  public:
    float X;
    float Y;

    explicit MousePositionEvent(float x, float y) :
        Event(EventCategory::MouseEvent),
        X(x), Y(y) {}
  };

  class MouseButtonEvent final : public Event {
  public:
    unsigned int Key;

    explicit MouseButtonEvent(unsigned int key) :
        Event(EventCategory::MouseEvent),
        Key(key) {}
  };

  class MouseScrollEvent final : public Event {
  public:
    float X;
    float Y;

    explicit MouseScrollEvent(float x, float y) :
        Event(EventCategory::MouseEvent),
        X(x), Y(y) {}
  };
}