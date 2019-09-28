#ifndef VEGA_MOUSEVENT_HPP
#define VEGA_MOUSEVENT_HPP

#include <sstream>
#include <string>

#include <Vega/Event/Event.hpp>

namespace Vega {
  class MouseMovedEvent final : public Event {
  public:
    explicit MouseMovedEvent(float x, float y) : mX(x), mY(y) {}

    inline float GetX() const { return mX; }
    inline float GetY() const { return mY; }

    std::string ToString() const override {
      std::stringstream ss;

      ss << "MouseMovedEvent: " << mX << " " << mY;

      return ss.str();
    }

    EVENT_CLASS_TYPE(MouseMoved)
    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

  private:
    float mX, mY;
  };

  class MouseScrolledEvent final : public Event {
  public:
    explicit MouseScrolledEvent(float xOffset, float yOffset) : mXOffset(xOffset), mYOffset(yOffset) {}

    inline float GetXOffset() const { return mXOffset; }
    inline float GetYOffset() const { return mYOffset; }

    std::string ToString() const override {
      std::stringstream ss;

      ss << "MouseScrolledEvent: " << mXOffset << " " << mYOffset;

      return ss.str();
    }

    EVENT_CLASS_TYPE(MouseScrolled)
    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

  private:
    float mXOffset, mYOffset;
  };

  class MouseButtonEvent : public Event {
  public:
    inline unsigned int GetMouseButton() const { return mButton; }

    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

  protected:
    explicit MouseButtonEvent(unsigned int button) : mButton(button) {};

    unsigned int mButton;
  };

  class MouseButtonPressedEvent final : public MouseButtonEvent {
  public:
    explicit MouseButtonPressedEvent(unsigned int button) : MouseButtonEvent(button) {}

    std::string ToString() const override {
      std::stringstream ss;

      ss << "MouseButtonPressedEvent: " << mButton;

      return ss.str();
    }

    EVENT_CLASS_TYPE(MouseButtonPressed)
  };

  class MouseButtonReleasedEvent final : public MouseButtonEvent {
  public:
    explicit MouseButtonReleasedEvent(unsigned int button) : MouseButtonEvent(button) {}

    std::string ToString() const override {
      std::stringstream ss;

      ss << "MouseButtonReleasedEvent: " << mButton;

      return ss.str();
    }

    EVENT_CLASS_TYPE(MouseButtonReleased)
  };
}

#endif