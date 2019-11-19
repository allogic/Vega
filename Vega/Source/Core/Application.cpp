#include <glad/glad.h>

#include <Core/Application.hpp>

void Vega::Core::Application::Run() {
  float lastTime = 0;

  float lastUpdateTime = 0;
  float lastFrameTime = 0;

  while (mRunning) {
    auto now = static_cast<float>(glfwGetTime());
    float deltaTime = now - lastTime;

    glfwPollEvents();

    if ((now - lastUpdateTime) >= mUPSLimit) {
      mConfigLoader.Update();

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