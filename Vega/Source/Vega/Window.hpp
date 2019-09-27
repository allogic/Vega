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
                    unsigned int antialiasing) :
        mWidth(width),
        mHeight(height) {
      assert(glfwInit() && "Failed to initialize glfw");

      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, static_cast<int>(major));
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, static_cast<int>(minor));
      glfwWindowHint(GLFW_SAMPLES, static_cast<int>(antialiasing));
      glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
      glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

      mGLFWwindow = glfwCreateWindow(static_cast<int>(width), static_cast<int>(height), title.c_str(), nullptr,
                                     nullptr);

      assert(mGLFWwindow && "Failed to create window");

      glfwMakeContextCurrent(mGLFWwindow);

      assert(gladLoadGL() && "Failed to initialize glad");
    }

    virtual ~Window() {
      glfwDestroyWindow(mGLFWwindow);

      glfwTerminate();
    };

    [[nodiscard]] inline unsigned int GetWidth() const { return mWidth; };
    [[nodiscard]] inline unsigned int GetHeight() const { return mHeight; };

    [[nodiscard]] inline float AspectRatio() const {
      return static_cast<float>(mWidth) / static_cast<float>(mHeight);
    }

    void SetEventCallback(const EventCallbackFunction &callback) {};

    [[nodiscard]] inline GLFWwindow &GetNativeWindow() const { return *mGLFWwindow; };

  private:
    unsigned int mWidth;
    unsigned int mHeight;

    GLFWwindow *mGLFWwindow;
  };
}

#endif