#pragma once

namespace Vega::Event {
  enum class EventCategory {
    None,
    WindowEvent,
    MouseEvent,
    KeyEvent,
  };

  enum class EventType {
    None,
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