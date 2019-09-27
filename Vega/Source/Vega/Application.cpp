#include <Vega/Application.hpp>

#include <Vega/ImGui/ImGuiLayer.hpp>

Vega::Application *Vega::Application::sInstance = nullptr;

Vega::Application::Application(const std::string &title,
                               unsigned int width,
                               unsigned int height,
                               unsigned int major,
                               unsigned int minor,
                               unsigned int antialiasing) {
  assert(!sInstance && "Application already exists");
  sInstance = this;

  mWindow = new Window(title, width, height, major, minor, antialiasing);

  mImGuiLayer = new ImGuiLayer();
  PushLayer(mImGuiLayer);
}

void Vega::Application::Run() {
  double lastUpdateTime = 0;
  double lastFrameTime = 0;

  while (!glfwWindowShouldClose(&mWindow->GetNativeWindow())) {
    double now = glfwGetTime();
    double deltaTime = now - lastUpdateTime;

    glfwPollEvents();

    for (auto layer : mLayerStack) layer->OnUpdate(deltaTime);

    if ((now - lastFrameTime) >= mFPSLimit) {
      glClearColor(0.f, 0.f, 0.f, 1.f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      for (auto layer : mLayerStack) layer->OnDraw();

      mImGuiLayer->Begin();
      for (auto layer : mLayerStack) layer->OnImGui(deltaTime);
      mImGuiLayer->End();

      glfwSwapBuffers(&mWindow->GetNativeWindow());

      lastFrameTime = now;
    }

    lastUpdateTime = now;
  }
}