#ifndef VEGA_KEYEVENT_HPP
#define VEGA_KEYEVENT_HPP

#include <sstream>
#include <string>

#include <Vega/Event/Event.hpp>

namespace Vega {
  class KeyEvent : public Event {
  public:
    inline unsigned int GetKeyCode() const { return mKeyCode; }

    EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

  protected:
    explicit KeyEvent(unsigned int keycode) : mKeyCode(keycode) {};

    unsigned int mKeyCode;
  };

  class KeyPressedEvent final : public KeyEvent {
  public:
    explicit KeyPressedEvent(unsigned int keycode, unsigned int repeatCount) : KeyEvent(keycode), mRepeatCount(repeatCount) {}

    inline unsigned int GetRepeatCount() const { return mRepeatCount; }

    std::string ToString() const override {
      std::stringstream ss;

      ss << "KeyPressedEvent: " << mKeyCode << " (" << mRepeatCount << " repeats)";

      return ss.str();
    }

    EVENT_CLASS_TYPE(KeyPressed)

  private:
    unsigned int mRepeatCount;
  };

  class KeyReleasedEvent final : public KeyEvent {
  public:
    explicit KeyReleasedEvent(unsigned int keycode) : KeyEvent(keycode) {}

    std::string ToString() const override {
      std::stringstream ss;

      ss << "KeyReleasedEvent: " << mKeyCode;

      return ss.str();
    }

    EVENT_CLASS_TYPE(KeyReleased)
  };

  class KeyTypedEvent final : public KeyEvent {
  public:
    explicit KeyTypedEvent(unsigned int keycode) : KeyEvent(keycode) {}

    std::string ToString() const override {
      std::stringstream ss;

      ss << "KeyTypedEvent: " << mKeyCode;

      return ss.str();
    }

    EVENT_CLASS_TYPE(KeyTyped)
  };
}

#endif