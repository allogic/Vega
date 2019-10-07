#pragma once

#include <Vega/Event/Event.hpp>

namespace Vega {
  class WindowCloseEvent final : public Event {

  };

  class WindowResizeEvent final : public Event {
  public:
    unsigned int Width;
    unsigned int Height;

    explicit WindowResizeEvent(unsigned int width, unsigned int height) : Width(width), Height(height) {}
  };
}