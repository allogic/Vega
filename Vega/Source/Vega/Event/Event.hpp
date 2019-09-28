#ifndef VEGA_EVENT_HPP
#define VEGA_EVENT_HPP

#include <iostream>
#include <string>

#include <Vega/Core.hpp>

#define EVENT_CLASS_TYPE(type) \
                static EventType GetStaticType() { return EventType::type; } \
                virtual EventType GetEventType() const override { return GetStaticType(); } \
                virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) \
                virtual unsigned int GetCategoryFlags() const override { return category; }

namespace Vega {
  enum class EventType {
    None = 0,
    WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
    KeyPressed, KeyReleased, KeyTyped,
    MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled,
  };

  enum EventCategory {
    None = 0,
    EventCategoryApplication = BIT(0),
    EventCategoryInput = BIT(1),
    EventCategoryKeyboard = BIT(2),
    EventCategoryMouse = BIT(3),
    EventCategoryMouseButton = BIT(4),
  };

  class Event {
  public:
    bool Handled = false;

    virtual EventType GetEventType() const = 0;
    virtual const char *GetName() const = 0;
    virtual unsigned int GetCategoryFlags() const = 0;
    virtual std::string ToString() const { return GetName(); }

    inline bool IsInCategory(EventCategory category) { return GetCategoryFlags() & category; }

    inline friend std::ostream &operator<<(std::ostream &os, const Event &e) { return os << e.ToString(); }
  };

  class EventDispatcher final {
  public:
    explicit EventDispatcher(Event &event) : mEvent(event) {}

    template<typename T, typename F>
    bool Dispatch(const F &func) {
      if (mEvent.GetEventType() == T::GetStaticType()) {
        mEvent.Handled = func(static_cast<T &>(mEvent));

        return true;
      }

      return false;
    }

  private:
    Event &mEvent;
  };
}

#endif