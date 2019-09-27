#ifndef VEGA_IMGUILAYER_HPP
#define VEGA_IMGUILAYER_HPP

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

#include <Vega/Layer.hpp>

namespace Vega {
  class ImGuiLayer final : public Layer {
  public:
    explicit ImGuiLayer() = default;

    ~ImGuiLayer() final = default;

    void OnAttach() override {
      IMGUI_CHECKVERSION();

      ImGui::CreateContext();
      ImGui::StyleColorsDark();

      auto window = &Vega::Application::GetApplication().GetWindow().GetNativeWindow();

      ImGui_ImplGlfw_InitForOpenGL(window, true);
      ImGui_ImplOpenGL3_Init("#version 430");
    }

    void OnDetach() override {
      ImGui_ImplOpenGL3_Shutdown();
      ImGui_ImplGlfw_Shutdown();

      ImGui::DestroyContext();
    }

    void Begin() {
      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();

      ImGui::NewFrame();
    }

    void End() {
      ImGui::EndFrame();

      ImGui::Render();
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
  };
}

#endif