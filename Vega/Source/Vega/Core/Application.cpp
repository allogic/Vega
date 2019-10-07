#include <Vega/Core/Application.hpp>

Vega::Application::Application(const std::string &title,
                               unsigned int width,
                               unsigned int height,
                               unsigned int antialiasing) :
    mWindowSize({width, height}) {
  auto &window = Window::Get(title, width, height, antialiasing);
  window.SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

  ResourceManager::Get("/home/michael/Downloads/Vega/Sandbox");

#ifdef VEGA_ENABLE_GUI
  Gui::Get("430");

  ImGuiIO &io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
#endif
}

Vega::Application::~Application() {
#ifdef VEGA_ENABLE_GUI
  Vega::Gui::Delete();
#endif

  Vega::Window::Delete();
}

void Vega::Application::Run() {
  float lastUpdateTime = 0;
  float lastFrameTime = 0;

  while (mRunning) {
    auto now = static_cast<float>(glfwGetTime());
    float deltaTime = now - lastUpdateTime;

    glfwPollEvents();

    OnUpdate();

    if ((now - lastFrameTime) >= mFPSLimit) {
      glClearColor(0.f, 0.f, 0.f, 1.f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      OnDraw();

#ifdef VEGA_ENABLE_GUI
      Gui::Get().Begin();

      ImGui::ShowDemoWindow();

      Debug::Draw();

      OnGui();

      Gui::Get().End();
#endif

      glfwSwapBuffers(&Window::Get().GetNativeWindow());

      lastFrameTime = now;
    }

    lastUpdateTime = now;
  }
}

void Vega::Application::OnEvent(const Vega::Event &event) {
  WindowClose(event);
  WindowResize(event);

  MouseScroll(event);
  MousePosition(event);
}

bool Vega::Application::KeyPressed(const Event &event, unsigned int key) const {
  if (event.Category != EventCategory::KeyEvent) return false;
  if (event.Type != EventType::KeyPressed) return false;

  return reinterpret_cast<const KeyEvent &>(event).Key == key;
}

bool Vega::Application::KeyHeld(const Event &event, unsigned int key) const {
  if (event.Category != EventCategory::KeyEvent) return false;
  if (event.Type != EventType::KeyHeld) return false;

  return reinterpret_cast<const KeyEvent &>(event).Key == key;
}

bool Vega::Application::KeyReleased(const Event &event, unsigned int key) const {
  if (event.Category != EventCategory::KeyEvent) return false;
  if (event.Type != EventType::KeyReleased) return false;

  return reinterpret_cast<const KeyEvent &>(event).Key == key;
}

bool Vega::Application::MousePressed(const Vega::Event &event, unsigned int key) const {
  if (event.Category != EventCategory::MouseEvent) return false;
  if (event.Type != EventType::MousePressed) return false;

  return reinterpret_cast<const MouseButtonEvent &>(event).Key == key;
}

bool Vega::Application::MouseHeld(const Vega::Event &event, unsigned int key) const {
  if (event.Category != EventCategory::MouseEvent) return false;
  if (event.Type != EventType::MouseHeld) return false;

  return reinterpret_cast<const MouseButtonEvent &>(event).Key == key;
}

bool Vega::Application::MouseReleased(const Vega::Event &event, unsigned int key) const {
  if (event.Category != EventCategory::MouseEvent) return false;
  if (event.Type != EventType::MouseReleased) return false;

  return reinterpret_cast<const MouseButtonEvent &>(event).Key == key;
}

void Vega::Application::WindowClose(const Vega::Event &event) {
  if (event.Category != EventCategory::WindowEvent) return;
  if (event.Type != EventType::WindowClose) return;

  mRunning = false;
}

void Vega::Application::WindowResize(const Vega::Event &event) {
  if (event.Category != EventCategory::WindowEvent) return;
  if (event.Type != EventType::WindowResize) return;

  const auto &windowResizeEvent = reinterpret_cast<const WindowResizeEvent &>(event);

  mWindowSize = {windowResizeEvent.Width, windowResizeEvent.Height};
}

void Vega::Application::MouseScroll(const Vega::Event &event) {
  if (event.Category != EventCategory::MouseEvent) return;
  if (event.Type != EventType::MouseScroll) return;

  const auto &mouseScrollEvent = reinterpret_cast<const MouseScrollEvent &>(event);

  mMouseScoll = {mouseScrollEvent.X, mouseScrollEvent.Y};
}

void Vega::Application::MousePosition(const Vega::Event &event) {
  if (event.Category != EventCategory::MouseEvent) return;
  if (event.Type != EventType::MousePosition) return;

  const auto &mousePositionEvent = reinterpret_cast<const MousePositionEvent &>(event);

  mMousePosition = {mousePositionEvent.X, mousePositionEvent.Y};
}