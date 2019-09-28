#ifndef VEGA_APPLICATIONEVENT_HPP
#define VEGA_APPLICATIONEVENT_HPP

#include <sstream>
#include <string>

#include <Vega/Event/Event.hpp>

namespace Vega {
  class WindowResizeEvent final : public Event {
  public:
    explicit WindowResizeEvent(unsigned int width, unsigned int height) : mWidth(width), mHeight(height) {}

    inline unsigned int GetWidth() const { return mWidth; }
    inline unsigned int GetHeight() const { return mHeight; }

    std::string ToString() const override {
      std::stringstream ss;

      ss << "WindowResizeEvent: " << mWidth << " " << mHeight;

      return ss.str();
    }

    EVENT_CLASS_TYPE(WindowResize)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)

  private:
    unsigned int mWidth, mHeight;
  };

  class WindowCloseEvent final : public Event {
  public:
    explicit WindowCloseEvent() = default;

    EVENT_CLASS_TYPE(WindowClose)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
  };
}

#endif