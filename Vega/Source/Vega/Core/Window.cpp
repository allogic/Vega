#include <Vega/Core/Window.hpp>

Vega::Window::Window(const std::string &title,
                     unsigned int width,
                     unsigned int height,
                     unsigned int antialiasing) {
  unsigned int glfwError = glfwInit();

  VEGA_ASSERT(glfwError, "Failed to initialize glfw")

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, VEGA_GL_MAJOR);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, VEGA_GL_MINOR);
  glfwWindowHint(GLFW_SAMPLES, static_cast<int>(antialiasing));
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  mGLFWwindow = glfwCreateWindow(static_cast<int>(width), static_cast<int>(height), title.c_str(), nullptr,
                                 nullptr);

  VEGA_ASSERT(mGLFWwindow, "Failed to create window")

  glfwMakeContextCurrent(mGLFWwindow);

  glfwSetWindowSizeCallback(mGLFWwindow, [](GLFWwindow *window, int width, int height) {
    //EntityManager::Get().Events().emit<WindowResizeEvent>(width, height);
  });

  glfwSetKeyCallback(mGLFWwindow, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
    //EntityManager::Get().Events().emit<KeyEvent>(static_cast<unsigned int>(key), static_cast<unsigned int>(action));
  });

  glfwSetScrollCallback(mGLFWwindow, [](GLFWwindow *window, double x, double y) {
    //EntityManager::Get().Events().emit<MouseScrollEvent>(static_cast<float>(x), static_cast<float>(y));
  });

  glfwSetCursorPosCallback(mGLFWwindow, [](GLFWwindow *window, double x, double y) {
    //EntityManager::Get().Events().emit<MousePositionEvent>(static_cast<float>(x), static_cast<float>(y));
  });

  unsigned int gladError = gladLoadGL();

  VEGA_ASSERT(gladError, "Failed to initialize glad")
}

Vega::Window::~Window() {
  glfwDestroyWindow(mGLFWwindow);

  glfwTerminate();
}