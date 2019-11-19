#ifndef WINDOWEVENT_HPP
#define WINDOWEVENT_HPP

#pragma once

#include <Event/Event.hpp>

namespace Vega::Event {
  class WindowCloseEvent final : public Event {
  public:
    explicit WindowCloseEvent() :
        Event(EventCategory::WindowEvent) {}
  };

  class WindowResizeEvent final : public Event {
  public:
    unsigned int Width;
    unsigned int Height;

    explicit WindowResizeEvent(unsigned int width, unsigned int height) :
        Event(EventCategory::WindowEvent),
        Width(width), Height(height) {}
  };
}

#endif