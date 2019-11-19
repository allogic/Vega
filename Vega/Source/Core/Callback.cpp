#include <Core/Callback.hpp>

Vega::Core::Callback::Callback() {
  /*glfwSetWindowUserPointer(mWindow->mWindow, &mEventCallback);

  mEventCallback = std::bind(&Callback::OnEvent, this, std::placeholders::_1);

  glfwSetWindowCloseCallback(mWindow->mWindow, [](GLFWwindow *window) {
    Event::WindowCloseEvent event;
    event.Type = Event::EventType::WindowClose;

    (*reinterpret_cast<EventCallback *>(glfwGetWindowUserPointer(window)))(event);
  });

  glfwSetWindowSizeCallback(mWindow->mWindow, [](GLFWwindow *window, int width, int height) {
    Event::WindowResizeEvent event(static_cast<unsigned int>(width), static_cast<unsigned int>(height));
    event.Type = Event::EventType::WindowResize;

    (*reinterpret_cast<EventCallback *>(glfwGetWindowUserPointer(window)))(event);
  });

  glfwSetCursorPosCallback(mWindow->mWindow, [](GLFWwindow *window, double x, double y) {
    Event::MousePositionEvent event(static_cast<float>(x), static_cast<float>(y));
    event.Type = Event::EventType::MousePosition;

    (*reinterpret_cast<EventCallback *>(glfwGetWindowUserPointer(window)))(event);
  });

  glfwSetScrollCallback(mWindow->mWindow, [](GLFWwindow *window, double x, double y) {
    Event::MouseScrollEvent event(static_cast<float>(x), static_cast<float>(y));
    event.Type = Event::EventType::MouseScroll;

    (*reinterpret_cast<EventCallback *>(glfwGetWindowUserPointer(window)))(event);
  });

  glfwSetKeyCallback(mWindow->mWindow, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
    EventCallback &callback = *static_cast<EventCallback *>(glfwGetWindowUserPointer(window));

    Event::KeyEvent event(static_cast<unsigned int>(key));

    if (action == GLFW_PRESS) event.Type = Event::EventType::KeyPressed;
    if (action == GLFW_REPEAT) event.Type = Event::EventType::KeyHeld;
    if (action == GLFW_RELEASE) event.Type = Event::EventType::KeyReleased;

    (*reinterpret_cast<EventCallback *>(glfwGetWindowUserPointer(window)))(event);
  });

  glfwSetMouseButtonCallback(mWindow->mWindow, [](GLFWwindow *window, int button, int action, int mods) {
    EventCallback &callback = *static_cast<EventCallback *>(glfwGetWindowUserPointer(window));

    Event::MouseButtonEvent event(static_cast<unsigned int>(button));

    if (action == GLFW_PRESS) event.Type = Event::EventType::MousePressed;
    if (action == GLFW_REPEAT) event.Type = Event::EventType::MouseHeld;
    if (action == GLFW_RELEASE) event.Type = Event::EventType::MouseReleased;

    (*reinterpret_cast<EventCallback *>(glfwGetWindowUserPointer(window)))(event);
  });*/
}

void Vega::Core::Callback::OnEvent(const Event::Event &event) {
  if (OnWindowClose(event)) return;
  if (OnWindowResize(event)) return;

  if (OnMousePosition(event)) return;
  if (OnMouseScroll(event)) return;
}

bool Vega::Core::Callback::OnWindowClose(const Event::Event &event) {
  if (event.Category != Event::EventCategory::WindowEvent || event.Type != Event::EventType::WindowClose) return false;
  const auto &windowCloseEvent = reinterpret_cast<const Event::WindowCloseEvent &>(event);

  //mApplication->mRunning = false; //TODO fix me

  return true;
}

bool Vega::Core::Callback::OnWindowResize(const Event::Event &event) {
  if (event.Category != Event::EventCategory::WindowEvent || event.Type != Event::EventType::WindowResize) return false;
  const auto &windowResizeEvent = reinterpret_cast<const Event::WindowResizeEvent &>(event);

  //mApplication->mWindowSize = {windowResizeEvent.Width, windowResizeEvent.Height}; //TODO fix me

  return true;
}

bool Vega::Core::Callback::OnMousePosition(const Event::Event &event) {
  if (event.Category != Event::EventCategory::MouseEvent || event.Type != Event::EventType::MousePosition) return false;
  const auto &mousePositionEvent = reinterpret_cast<const Event::MousePositionEvent &>(event);

  //mApplication->mMousePosition = {mousePositionEvent.X, mousePositionEvent.Y}; //TODO fix me

  return true;
}

bool Vega::Core::Callback::OnMouseScroll(const Event::Event &event) {
  if (event.Category != Event::EventCategory::MouseEvent || event.Type != Event::EventType::MouseScroll) return false;
  const auto &mouseScrollEvent = reinterpret_cast<const Event::MouseScrollEvent &>(event);

  //mApplication->mMouseScoll = {mouseScrollEvent.X, mouseScrollEvent.Y}; //TODO fix me

  return true;
}

bool Vega::Core::Callback::KeyPressed(const Event::Event &event, unsigned int key) const {
  if (event.Category != Event::EventCategory::KeyEvent || event.Type != Event::EventType::KeyPressed) return false;
  return reinterpret_cast<const Event::KeyEvent &>(event).Key == key;
}

bool Vega::Core::Callback::KeyHeld(const Event::Event &event, unsigned int key) const {
  if (event.Category != Event::EventCategory::KeyEvent || event.Type != Event::EventType::KeyHeld) return false;
  return reinterpret_cast<const Event::KeyEvent &>(event).Key == key;
}

bool Vega::Core::Callback::KeyReleased(const Event::Event &event, unsigned int key) const {
  if (event.Category != Event::EventCategory::KeyEvent || event.Type != Event::EventType::KeyReleased) return false;
  return reinterpret_cast<const Event::KeyEvent &>(event).Key == key;
}

bool Vega::Core::Callback::MousePressed(const Vega::Event::Event &event, unsigned int key) const {
  if (event.Category != Event::EventCategory::MouseEvent || event.Type != Event::EventType::MousePressed) return false;
  return reinterpret_cast<const Event::MouseButtonEvent &>(event).Key == key;
}

bool Vega::Core::Callback::MouseHeld(const Vega::Event::Event &event, unsigned int key) const {
  if (event.Category != Event::EventCategory::MouseEvent || event.Type != Event::EventType::MouseHeld) return false;
  return reinterpret_cast<const Event::MouseButtonEvent &>(event).Key == key;
}

bool Vega::Core::Callback::MouseReleased(const Vega::Event::Event &event, unsigned int key) const {
  if (event.Category != Event::EventCategory::MouseEvent || event.Type != Event::EventType::MouseReleased) return false;
  return reinterpret_cast<const Event::MouseButtonEvent &>(event).Key == key;
}