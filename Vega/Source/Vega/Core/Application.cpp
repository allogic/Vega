#include <Vega/Core/Application.hpp>

Vega::Core::Application::Application(const std::string &title,
                                     unsigned int width,
                                     unsigned int height,
                                     unsigned int antialiasing) :
    mWindowSize({width, height}) {
  VEGA_RUNTIME_ERROR(!glfwInit(), "Failed to initialize glfw");

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, VEGA_GL_MAJOR);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, VEGA_GL_MINOR);
  glfwWindowHint(GLFW_SAMPLES, static_cast<int>(antialiasing));
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  mWindow = glfwCreateWindow(static_cast<int>(width), static_cast<int>(height), title.c_str(), nullptr,
                             nullptr);

  VEGA_RUNTIME_ERROR(!mWindow, "Failed to create window");

  glfwMakeContextCurrent(mWindow);
  glfwSetWindowUserPointer(mWindow, &mEventCallback);

  mEventCallback = std::bind(&Application::OnEvent, this, std::placeholders::_1);

  glfwSetWindowCloseCallback(mWindow, [](GLFWwindow *window) {
    Event::WindowCloseEvent event;
    event.Type = Event::EventType::WindowClose;

    (*reinterpret_cast<EventCallback *>(glfwGetWindowUserPointer(window)))(event);
  });

  glfwSetWindowSizeCallback(mWindow, [](GLFWwindow *window, int width, int height) {
    Event::WindowResizeEvent event(static_cast<unsigned int>(width), static_cast<unsigned int>(height));
    event.Type = Event::EventType::WindowResize;

    (*reinterpret_cast<EventCallback *>(glfwGetWindowUserPointer(window)))(event);
  });

  glfwSetCursorPosCallback(mWindow, [](GLFWwindow *window, double x, double y) {
    Event::MousePositionEvent event(static_cast<float>(x), static_cast<float>(y));
    event.Type = Event::EventType::MousePosition;

    (*reinterpret_cast<EventCallback *>(glfwGetWindowUserPointer(window)))(event);
  });

  glfwSetScrollCallback(mWindow, [](GLFWwindow *window, double x, double y) {
    Event::MouseScrollEvent event(static_cast<float>(x), static_cast<float>(y));
    event.Type = Event::EventType::MouseScroll;

    (*reinterpret_cast<EventCallback *>(glfwGetWindowUserPointer(window)))(event);
  });

  glfwSetKeyCallback(mWindow, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
    EventCallback &callback = *static_cast<EventCallback *>(glfwGetWindowUserPointer(window));

    Event::KeyEvent event(static_cast<unsigned int>(key));

    if (action == GLFW_PRESS) event.Type = Event::EventType::KeyPressed;
    if (action == GLFW_REPEAT) event.Type = Event::EventType::KeyHeld;
    if (action == GLFW_RELEASE) event.Type = Event::EventType::KeyReleased;

    (*reinterpret_cast<EventCallback *>(glfwGetWindowUserPointer(window)))(event);
  });

  glfwSetMouseButtonCallback(mWindow, [](GLFWwindow *window, int button, int action, int mods) {
    EventCallback &callback = *static_cast<EventCallback *>(glfwGetWindowUserPointer(window));

    Event::MouseButtonEvent event(static_cast<unsigned int>(button));

    if (action == GLFW_PRESS) event.Type = Event::EventType::MousePressed;
    if (action == GLFW_REPEAT) event.Type = Event::EventType::MouseHeld;
    if (action == GLFW_RELEASE) event.Type = Event::EventType::MouseReleased;

    (*reinterpret_cast<EventCallback *>(glfwGetWindowUserPointer(window)))(event);
  });

  VEGA_RUNTIME_ERROR(!gladLoadGL(), "Failed to initialize glad");

#ifdef VEGA_ENABLE_GUI
  IMGUI_CHECKVERSION();

  ImGui::CreateContext();
  ImGui::StyleColorsDark();

  ImGui_ImplGlfw_InitForOpenGL(mWindow, true);
  ImGui_ImplOpenGL3_Init("#version " VEGA_GUI_VERSION);

  ImGuiIO &io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

  ImGuiStyle &style = ImGui::GetStyle();
  style.WindowBorderSize = 0.f;
#endif

  VEGA_INSTANCE(ModuleLoader, fs::path{Filesystem::RootPath + "Sandbox/Module"}).DebugReloadIfChanged();
  VEGA_INSTANCE(ShaderLoader, fs::path{Filesystem::RootPath + "Sandbox/Shader"}).DebugReloadIfChanged();
}

Vega::Core::Application::~Application() {
#ifdef VEGA_ENABLE_GUI
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();

  ImGui::DestroyContext();
#endif

  glfwDestroyWindow(mWindow);
  glfwTerminate();
}

void Vega::Core::Application::Run() {
  float lastUpdateTime = 0;
  float lastFrameTime = 0;

  while (mRunning) {
    auto now = static_cast<float>(glfwGetTime());
    float deltaTime = now - lastUpdateTime;

    glfwPollEvents();

    OnUpdate();
    VEGA_INSTANCE(ModuleLoader).OnUpdate(deltaTime);

    if ((now - lastFrameTime) >= mFPSLimit) {
      glClearColor(0.f, 0.f, 0.f, 1.f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      OnDraw();

#ifdef VEGA_ENABLE_GUI
      VEGA_INSTANCE(ModuleLoader).DebugReloadIfChanged();
      VEGA_INSTANCE(ShaderLoader).DebugReloadIfChanged();

      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();

      ImGui::NewFrame();

      ImGui::ShowDemoWindow();

      Debug::Draw();

      OnGui();

      ImGui::EndFrame();

      ImGui::Render();
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif

      glfwSwapBuffers(mWindow);

      lastFrameTime = now;
    }

    lastUpdateTime = now;
  }
}

void Vega::Core::Application::OnEvent(const Vega::Event::Event &event) {
  if (OnWindowClose(event)) return;
  if (OnWindowResize(event)) return;

  if (OnMousePosition(event)) return;
  if (OnMouseScroll(event)) return;
}

bool Vega::Core::Application::OnWindowClose(const Vega::Event::Event &event) {
  if (event.Category != Event::EventCategory::WindowEvent || event.Type != Event::EventType::WindowClose) return false;

  const auto &windowCloseEvent = reinterpret_cast<const Event::WindowCloseEvent &>(event);

  mRunning = false;

  return true;
}

bool Vega::Core::Application::OnWindowResize(const Vega::Event::Event &event) {
  if (event.Category != Event::EventCategory::WindowEvent || event.Type != Event::EventType::WindowResize) return false;

  const auto &windowResizeEvent = reinterpret_cast<const Event::WindowResizeEvent &>(event);

  mWindowSize = {windowResizeEvent.Width, windowResizeEvent.Height};

  return true;
}

bool Vega::Core::Application::OnMousePosition(const Vega::Event::Event &event) {
  if (event.Category != Event::EventCategory::MouseEvent || event.Type != Event::EventType::MousePosition) return false;

  const auto &mousePositionEvent = reinterpret_cast<const Event::MousePositionEvent &>(event);

  mMousePosition = {mousePositionEvent.X, mousePositionEvent.Y};

  return true;
}

bool Vega::Core::Application::OnMouseScroll(const Vega::Event::Event &event) {
  if (event.Category != Event::EventCategory::MouseEvent || event.Type != Event::EventType::MouseScroll) return false;

  const auto &mouseScrollEvent = reinterpret_cast<const Event::MouseScrollEvent &>(event);

  mMouseScoll = {mouseScrollEvent.X, mouseScrollEvent.Y};

  return true;
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

bool Vega::Core::Application::MousePressed(const Vega::Event::Event &event, unsigned int key) const {
  if (event.Category != Event::EventCategory::MouseEvent || event.Type != Event::EventType::MousePressed) return false;

  return reinterpret_cast<const Event::MouseButtonEvent &>(event).Key == key;
}

bool Vega::Core::Application::MouseHeld(const Vega::Event::Event &event, unsigned int key) const {
  if (event.Category != Event::EventCategory::MouseEvent || event.Type != Event::EventType::MouseHeld) return false;

  return reinterpret_cast<const Event::MouseButtonEvent &>(event).Key == key;
}

bool Vega::Core::Application::MouseReleased(const Vega::Event::Event &event, unsigned int key) const {
  if (event.Category != Event::EventCategory::MouseEvent || event.Type != Event::EventType::MouseReleased) return false;

  return reinterpret_cast<const Event::MouseButtonEvent &>(event).Key == key;
}