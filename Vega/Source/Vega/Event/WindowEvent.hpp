#ifndef VEGA_WINDOWEVENT_HPP
#define VEGA_WINDOWEVENT_HPP

namespace Vega {
  class WindowResizeEvent final {
  public:
    unsigned int Width;
    unsigned int Height;

    explicit WindowResizeEvent(unsigned int width, unsigned int height) : Width(width), Height(height) {}
  };
}

#endif