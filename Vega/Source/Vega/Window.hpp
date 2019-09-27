#ifndef VEGA_WINDOW_HPP
#define VEGA_WINDOW_HPP

#include <functional>
#include <cassert>

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <Vega/Event.hpp>

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

    inline unsigned int GetWidth() const { return mWidth; };
    inline unsigned int GetHeight() const { return mHeight; };

    inline float AspectRatio() const {
      return static_cast<float>(mWidth) / static_cast<float>(mHeight);
    }

    inline void SetEventCallback(const EventCallbackFunction &callback) {};

    inline GLFWwindow &GetNativeWindow() const { return *mGLFWwindow; };

  private:
    unsigned int mWidth;
    unsigned int mHeight;

    GLFWwindow *mGLFWwindow;
  };
}

#endif