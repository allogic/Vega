#include <Vega/Window.hpp>

Vega::Window::Window(const std::string &title,
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

Vega::Window::~Window() {
  glfwDestroyWindow(mGLFWwindow);

  glfwTerminate();
};