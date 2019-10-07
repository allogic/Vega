#include <Vega/Core/Window.hpp>

Vega::Window::Window(const std::string &title,
                     unsigned int width,
                     unsigned int height,
                     unsigned int antialiasing) {
  VEGA_RUNTIME_ERROR(!glfwInit(), "Failed to initialize glfw");

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, VEGA_GL_MAJOR);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, VEGA_GL_MINOR);
  glfwWindowHint(GLFW_SAMPLES, static_cast<int>(antialiasing));
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  mGLFWwindow = glfwCreateWindow(static_cast<int>(width), static_cast<int>(height), title.c_str(), nullptr,
                                 nullptr);

  VEGA_RUNTIME_ERROR(!mGLFWwindow, "Failed to create window");

  glfwMakeContextCurrent(mGLFWwindow);
  glfwSetWindowUserPointer(mGLFWwindow, &mEventCallback);

  glfwSetWindowCloseCallback(mGLFWwindow, [](GLFWwindow *window) {
    EventCallback &callback = *static_cast<EventCallback *>(glfwGetWindowUserPointer(window));

    WindowCloseEvent event;

    event.Category = EventCategory::WindowEvent;
    event.Type = EventType::WindowClose;

    callback(event);
  });

  glfwSetWindowSizeCallback(mGLFWwindow, [](GLFWwindow *window, int width, int height) {
    EventCallback &callback = *static_cast<EventCallback *>(glfwGetWindowUserPointer(window));

    WindowResizeEvent event(static_cast<unsigned int>(width), static_cast<unsigned int>(height));

    event.Category = EventCategory::WindowEvent;
    event.Type = EventType::WindowResize;

    callback(event);
  });

  glfwSetKeyCallback(mGLFWwindow, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
    EventCallback &callback = *static_cast<EventCallback *>(glfwGetWindowUserPointer(window));

    KeyEvent event(static_cast<unsigned int>(key));

    event.Category = EventCategory::KeyEvent;

    if (action == GLFW_PRESS) event.Type = EventType::KeyPressed;
    if (action == GLFW_REPEAT) event.Type = EventType::KeyHeld;
    if (action == GLFW_RELEASE) event.Type = EventType::KeyReleased;

    callback(event);
  });

  glfwSetCursorPosCallback(mGLFWwindow, [](GLFWwindow *window, double x, double y) {
    EventCallback &callback = *static_cast<EventCallback *>(glfwGetWindowUserPointer(window));

    MousePositionEvent event(static_cast<float>(x), static_cast<float>(y));

    event.Category = EventCategory::MouseEvent;
    event.Type = EventType::MousePosition;

    callback(event);
  });

  glfwSetMouseButtonCallback(mGLFWwindow, [](GLFWwindow *window, int button, int action, int mods) {
    EventCallback &callback = *static_cast<EventCallback *>(glfwGetWindowUserPointer(window));

    MouseButtonEvent event(static_cast<unsigned int>(button));

    event.Category = EventCategory::MouseEvent;

    if (action == GLFW_PRESS) event.Type = EventType::MousePressed;
    if (action == GLFW_REPEAT) event.Type = EventType::MouseHeld;
    if (action == GLFW_RELEASE) event.Type = EventType::MouseReleased;

    callback(event);
  });

  glfwSetScrollCallback(mGLFWwindow, [](GLFWwindow *window, double x, double y) {
    EventCallback &callback = *static_cast<EventCallback *>(glfwGetWindowUserPointer(window));

    MouseScrollEvent event(static_cast<float>(x), static_cast<float>(y));

    event.Category = EventCategory::MouseEvent;
    event.Type = EventType::MouseScroll;

    callback(event);
  });

  VEGA_RUNTIME_ERROR(!gladLoadGL(), "Failed to initialize glad");
}

Vega::Window::~Window() {
  glfwDestroyWindow(mGLFWwindow);

  glfwTerminate();
}