#ifndef VEGA_WINDOW_HPP
#define VEGA_WINDOW_HPP

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <entityx/entityx.h>

#include <Vega/Core/Core.hpp>
#include <Vega/EntityManager.hpp>

#include <Vega/Event/WindowEvent.hpp>
#include <Vega/Event/MouseEvent.hpp>
#include <Vega/Event/KeyEvent.hpp>

namespace Vega {
  class Window final {
  SINGLETON(Window)

  public:
    inline GLFWwindow &GetNativeWindow() const { return *mGLFWwindow; };

  private:
    explicit Window() = default;

    explicit Window(const std::string &title,
                    unsigned int width,
                    unsigned int height,
                    unsigned int antialiasing);

    virtual ~Window();

  private:
    GLFWwindow *mGLFWwindow = nullptr;
  };
}

#endif