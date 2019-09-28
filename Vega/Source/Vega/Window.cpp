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

  glfwSetWindowUserPointer(mGLFWwindow, &mData);

  glfwSetWindowSizeCallback(mGLFWwindow, [](GLFWwindow *window, int width, int height) {});
  glfwSetWindowCloseCallback(mGLFWwindow, [](GLFWwindow *window) {});
  glfwSetKeyCallback(mGLFWwindow, [](GLFWwindow *window, int key, int scancode, int action, int mods) {});
  glfwSetCharCallback(mGLFWwindow, [](GLFWwindow *window, unsigned int keycode) {});
  glfwSetScrollCallback(mGLFWwindow, [](GLFWwindow *window, double x, double y) {});
  glfwSetCursorPosCallback(mGLFWwindow, [](GLFWwindow *window, double x, double y) {});

  /*glfwSetWindowSizeCallback(mGLFWwindow, [](GLFWwindow *window, int width, int height) {
    WindowData &data = *reinterpret_cast<WindowData *>(glfwGetWindowUserPointer(window));

    data.Width = width;
    data.Height = height;

    WindowResizeEvent event(width, height);

    data.EventCallback(event);
  });

  glfwSetWindowCloseCallback(mGLFWwindow, [](GLFWwindow *window) {
    WindowData &data = *reinterpret_cast<WindowData *>(glfwGetWindowUserPointer(window));

    WindowCloseEvent event;

    data.EventCallback(event);
  });

  glfwSetKeyCallback(mGLFWwindow, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
    WindowData &data = *reinterpret_cast<WindowData *>(glfwGetWindowUserPointer(window));

    switch (action) {
      case GLFW_PRESS: {
        KeyPressedEvent event(key, 0);

        data.EventCallback(event);
        break;
      }
      case GLFW_RELEASE: {
        KeyReleasedEvent event(key);

        data.EventCallback(event);
        break;
      }
      case GLFW_REPEAT: {
        KeyPressedEvent event(key, 1);

        data.EventCallback(event);
        break;
      }
      default: {
        break;
      }
    }
  });

  glfwSetCharCallback(mGLFWwindow, [](GLFWwindow *window, unsigned int keycode) {
    WindowData &data = *reinterpret_cast<WindowData *>(glfwGetWindowUserPointer(window));

    KeyTypedEvent event(keycode);

    data.EventCallback(event);
  });

  glfwSetMouseButtonCallback(mGLFWwindow, [](GLFWwindow *window, int button, int action, int mods) {
    WindowData &data = *reinterpret_cast<WindowData *>(glfwGetWindowUserPointer(window));

    switch (action) {
      case GLFW_PRESS: {
        MouseButtonPressedEvent event(button);

        data.EventCallback(event);
        break;
      }
      case GLFW_RELEASE: {
        MouseButtonReleasedEvent event(button);

        data.EventCallback(event);
        break;
      }
      default: {
        break;
      }
    }
  });

  glfwSetScrollCallback(mGLFWwindow, [](GLFWwindow *window, double x, double y) {
    WindowData &data = *reinterpret_cast<WindowData *>(glfwGetWindowUserPointer(window));

    MouseScrolledEvent event(static_cast<float>(x), static_cast<float>(y));

    data.EventCallback(event);
  });

  glfwSetCursorPosCallback(mGLFWwindow, [](GLFWwindow *window, double x, double y) {
    WindowData &data = *reinterpret_cast<WindowData *>(glfwGetWindowUserPointer(window));

    MouseMovedEvent event(static_cast<float>(x), static_cast<float>(y));

    data.EventCallback(event);
  });*/

  assert(gladLoadGL() && "Failed to initialize glad");
}

Vega::Window::~Window() {
  glfwDestroyWindow(mGLFWwindow);

  glfwTerminate();
};