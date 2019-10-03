#ifndef VEGA_MOUSEEVENT_HPP
#define VEGA_MOUSEEVENT_HPP

namespace Vega {
  class MousePositionEvent final {
  public:
    float X;
    float Y;

    explicit MousePositionEvent(float x, float y) : X(x), Y(y) {}
  };

  class MouseScrollEvent final {
  public:
    float X;
    float Y;

    explicit MouseScrollEvent(float x, float y) : X(x), Y(y) {}
  };
}

#endif