#ifndef EVENT_HPP
#define EVENT_HPP

#pragma once

namespace Vega::Event {
  enum class EventCategory : int {
    None = 0,
    WindowEvent,
    MouseEvent,
    KeyEvent,
  };

  enum class EventType : int {
    None = 0,
    WindowResize, WindowClose,
    MousePressed, MouseHeld, MouseReleased, MousePosition, MouseScroll,
    KeyPressed, KeyHeld, KeyReleased,
  };

  class Event {
  public:
    EventCategory Category = EventCategory::None;
    EventType Type = EventType::None;

  public:
    explicit Event(EventCategory category) : Category(category) {}
  };
}

#endif