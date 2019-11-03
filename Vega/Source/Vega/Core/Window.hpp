#pragma once

#include <Vega/Vendor/Glad.hpp>
#include <Vega/Vendor/Glfw.hpp>
#include <Vega/Vendor/Imgui.hpp>

#include <Vega/Core/Core.hpp>

#include <Vega/Utility/Settings.hpp>

namespace Vega::Core {
  class Window final {
    friend class Gui;
    friend class Application;
    friend class Callback;

  public:
    explicit Window(int width, int height) {
      VEGA_RUNTIME_ERROR(!glfwInit(), "Failed to initialize glfw");

      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, CONFIG_GET(int, "gl-major"));
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, CONFIG_GET(int, "gl-minor"));
      glfwWindowHint(GLFW_SAMPLES, CONFIG_GET(int, "antialiasing"));
      glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
      glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

      mWindow = glfwCreateWindow(width, height, CONFIG_GET(std::string, "title").c_str(), nullptr, nullptr);

      VEGA_RUNTIME_ERROR(!mWindow, "Failed to create window");

      glfwMakeContextCurrent(mWindow);

      VEGA_RUNTIME_ERROR(!gladLoadGL(), "Failed to initialize glad");
    }

    virtual ~Window() {
      glfwDestroyWindow(mWindow);
      glfwTerminate();
    }

  private:
    GLFWwindow *mWindow = nullptr;
  };
}