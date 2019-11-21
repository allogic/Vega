#include <glad/glad.h>

#include <Core/Application.hpp>

Vega::Core::Application::Application(GLFWwindow *window) {
  mCallback = &Application::OnEvent;

  glfwSetWindowUserPointer(window, reinterpret_cast<void *>(&mCallback));

  glfwSetWindowCloseCallback(window, [](GLFWwindow *window) {
    Event::WindowCloseEvent event;
    event.Type = Event::EventType::WindowClose;

    (*reinterpret_cast<EventCallback *>(glfwGetWindowUserPointer(window)))(event);
  });

  glfwSetWindowSizeCallback(window, [](GLFWwindow *window, int width, int height) {
    Event::WindowResizeEvent event(static_cast<unsigned int>(width), static_cast<unsigned int>(height));
    event.Type = Event::EventType::WindowResize;

    (*reinterpret_cast<EventCallback *>(glfwGetWindowUserPointer(window)))(event);
  });

  glfwSetCursorPosCallback(window, [](GLFWwindow *window, double x, double y) {
    Event::MousePositionEvent event(static_cast<float>(x), static_cast<float>(y));
    event.Type = Event::EventType::MousePosition;

    (*reinterpret_cast<EventCallback *>(glfwGetWindowUserPointer(window)))(event);
  });

  glfwSetScrollCallback(window, [](GLFWwindow *window, double x, double y) {
    Event::MouseScrollEvent event(static_cast<float>(x), static_cast<float>(y));
    event.Type = Event::EventType::MouseScroll;

    (*reinterpret_cast<EventCallback *>(glfwGetWindowUserPointer(window)))(event);
  });

  glfwSetKeyCallback(window, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
    EventCallback &callback = *static_cast<EventCallback *>(glfwGetWindowUserPointer(window));

    Event::KeyEvent event(static_cast<unsigned int>(key));

    if (action == GLFW_PRESS) event.Type = Event::EventType::KeyPressed;
    if (action == GLFW_REPEAT) event.Type = Event::EventType::KeyHeld;
    if (action == GLFW_RELEASE) event.Type = Event::EventType::KeyReleased;

    (*reinterpret_cast<EventCallback *>(glfwGetWindowUserPointer(window)))(event);
  });

  glfwSetMouseButtonCallback(window, [](GLFWwindow *window, int button, int action, int mods) {
    EventCallback &callback = *static_cast<EventCallback *>(glfwGetWindowUserPointer(window));

    Event::MouseButtonEvent event(static_cast<unsigned int>(button));

    if (action == GLFW_PRESS) event.Type = Event::EventType::MousePressed;
    if (action == GLFW_REPEAT) event.Type = Event::EventType::MouseHeld;
    if (action == GLFW_RELEASE) event.Type = Event::EventType::MouseReleased;

    (*reinterpret_cast<EventCallback *>(glfwGetWindowUserPointer(window)))(event);
  });
}

void Vega::Core::Application::Run() {
  float lastTime = 0;

  float lastUpdateTime = 0;
  float lastFrameTime = 0;

  while (mRunning) {
    auto now = static_cast<float>(glfwGetTime());
    float deltaTime = now - lastTime;

    glfwPollEvents();

    if ((now - lastUpdateTime) >= mUPSLimit) {
      //mConfigLoader.Update(); // fix me

      lastUpdateTime = now;
    }

    if ((now - lastFrameTime) >= mFPSLimit) {
      glClearColor(0.f, 0.f, 0.f, 1.f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();

      ImGui::NewFrame();

      //ImGui::ShowDemoWindow();

      ImGui::EndFrame();

      ImGui::Render();
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

      //glfwSwapBuffers(Window::sWindow); //TODO fix me

      lastFrameTime = now;
    }

    lastTime = now;
  }
}

bool Vega::Core::Application::KeyPressed(const Event::Event &event, unsigned int key) const {
  if (event.Category != Event::EventCategory::KeyEvent || event.Type != Event::EventType::KeyPressed) return false;
  return reinterpret_cast<const Event::KeyEvent &>(event).Key == key;
}

bool Vega::Core::Application::KeyHeld(const Event::Event &event, unsigned int key) const {
  if (event.Category != Event::EventCategory::KeyEvent || event.Type != Event::EventType::KeyHeld) return false;
  return reinterpret_cast<const Event::KeyEvent &>(event).Key == key;
}

bool Vega::Core::Application::KeyReleased(const Event::Event &event, unsigned int key) const {
  if (event.Category != Event::EventCategory::KeyEvent || event.Type != Event::EventType::KeyReleased) return false;
  return reinterpret_cast<const Event::KeyEvent &>(event).Key == key;
}

bool Vega::Core::Application::MousePressed(const Event::Event &event, unsigned int key) const {
  if (event.Category != Event::EventCategory::MouseEvent || event.Type != Event::EventType::MousePressed) return false;
  return reinterpret_cast<const Event::MouseButtonEvent &>(event).Key == key;
}

bool Vega::Core::Application::MouseHeld(const Event::Event &event, unsigned int key) const {
  if (event.Category != Event::EventCategory::MouseEvent || event.Type != Event::EventType::MouseHeld) return false;
  return reinterpret_cast<const Event::MouseButtonEvent &>(event).Key == key;
}

bool Vega::Core::Application::MouseReleased(const Event::Event &event, unsigned int key) const {
  if (event.Category != Event::EventCategory::MouseEvent || event.Type != Event::EventType::MouseReleased) return false;
  return reinterpret_cast<const Event::MouseButtonEvent &>(event).Key == key;
}

bool Vega::Core::Application::OnWindowClose(const Event::Event &event) const {
  if (event.Category != Event::EventCategory::WindowEvent || event.Type != Event::EventType::WindowClose) return false;
  const auto &windowCloseEvent = reinterpret_cast<const Event::WindowCloseEvent &>(event);

  //mApplication->mRunning = false; //TODO fix me

  return true;
}

void Vega::Core::Application::OnEvent(const Event::Event &event) {
  if (OnWindowClose(event)) return;
  if (OnWindowResize(event)) return;

  if (OnMousePosition(event)) return;
  if (OnMouseScroll(event)) return;
}

bool Vega::Core::Application::OnWindowResize(const Event::Event &event) const {
  if (event.Category != Event::EventCategory::WindowEvent || event.Type != Event::EventType::WindowResize) return false;
  const auto &windowResizeEvent = reinterpret_cast<const Event::WindowResizeEvent &>(event);

  //mApplication->mWindowSize = {windowResizeEvent.Width, windowResizeEvent.Height}; //TODO fix me

  return true;
}

bool Vega::Core::Application::OnMousePosition(const Event::Event &event) const {
  if (event.Category != Event::EventCategory::MouseEvent || event.Type != Event::EventType::MousePosition) return false;
  const auto &mousePositionEvent = reinterpret_cast<const Event::MousePositionEvent &>(event);

  //mApplication->mMousePosition = {mousePositionEvent.X, mousePositionEvent.Y}; //TODO fix me

  return true;
}

bool Vega::Core::Application::OnMouseScroll(const Event::Event &event) const {
  if (event.Category != Event::EventCategory::MouseEvent || event.Type != Event::EventType::MouseScroll) return false;
  const auto &mouseScrollEvent = reinterpret_cast<const Event::MouseScrollEvent &>(event);

  //mApplication->mMouseScoll = {mouseScrollEvent.X, mouseScrollEvent.Y}; //TODO fix me

  return true;
}