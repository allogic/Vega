#pragma once

#include <functional>

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <Vega/Core/Core.hpp>

#include <Vega/Event/WindowEvent.hpp>
#include <Vega/Event/MouseEvent.hpp>
#include <Vega/Event/KeyEvent.hpp>

namespace Vega {
  class Window final {
    using EventCallback = std::function<void(const Event &)>;

  SINGLETON(Window)

  public:
    inline GLFWwindow &GetNativeWindow() const { return *mGLFWwindow; };

    inline void SetEventCallback(const EventCallback &eventCallback) { mEventCallback = eventCallback; }

  private:
    explicit Window() = default;

    explicit Window(const std::string &title,
                    unsigned int width,
                    unsigned int height,
                    unsigned int antialiasing);

    virtual ~Window();

  private:
    GLFWwindow *mGLFWwindow = nullptr;

    EventCallback mEventCallback;
  };
}