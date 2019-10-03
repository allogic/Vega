#include <Vega/Core/Application.hpp>
#include "Gui.hpp"

Vega::Application::Application(const std::string &title,
                               unsigned int width,
                               unsigned int height,
                               unsigned int antialiasing) {
  Window::Get(title, width, height, antialiasing);

#ifdef VEGA_ENABLE_GUI
  Gui::Get("430");
#endif
}

void Vega::Application::Run() {
  float lastUpdateTime = 0;
  float lastFrameTime = 0;

  while (!glfwWindowShouldClose(&Window::Get().GetNativeWindow())) {
    auto now = static_cast<float>(glfwGetTime());
    float deltaTime = now - lastUpdateTime;

    glfwPollEvents();

    for (auto layer : mLayerStack) layer->OnUpdate(deltaTime);

    if ((now - lastFrameTime) >= mFPSLimit) {
      glClearColor(0.f, 0.f, 0.f, 1.f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      for (auto layer : mLayerStack) layer->OnDraw();

#ifdef VEGA_ENABLE_GUI
      Gui::Get().Begin();

      //ImGui::ShowDemoWindow();

      Debug::Draw();

      for (auto layer : mLayerStack) layer->OnImGui();

      Gui::Get().End();
#endif

      glfwSwapBuffers(&Window::Get().GetNativeWindow());

      lastFrameTime = now;
    }

    lastUpdateTime = now;
  }
}