#ifndef VEGA_WINDOW_HPP
#define VEGA_WINDOW_HPP

#include <functional>
#include <cassert>

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <Vega/Event/Event.hpp>
#include <Vega/Event/ApplicationEvent.hpp>
#include <Vega/Event/KeyEvent.hpp>
#include <Vega/Event/MouseEvent.hpp>

namespace Vega {
  class Window final {
    using EventCallbackFunction = std::function<void(Event &)>;

  public:
    explicit Window(const std::string &title,
                    unsigned int width,
                    unsigned int height,
                    unsigned int major,
                    unsigned int minor,
                    unsigned int antialiasing);

    virtual ~Window();

    inline unsigned int GetWidth() const { return mData.Width; };
    inline unsigned int GetHeight() const { return mData.Height; };

    inline float AspectRatio() const {
      return static_cast<float>(mData.Width) / static_cast<float>(mData.Height);
    }

    inline void SetEventCallback(const EventCallbackFunction &callback) { mData.EventCallback = callback; };

    inline GLFWwindow &GetNativeWindow() const { return *mGLFWwindow; };

  private:
    unsigned int mWidth;
    unsigned int mHeight;

    GLFWwindow *mGLFWwindow;

    struct WindowData {
      std::string Title;

      unsigned int Width;
      unsigned int Height;

      EventCallbackFunction EventCallback;
    };

    WindowData mData;
  };
}

#endif