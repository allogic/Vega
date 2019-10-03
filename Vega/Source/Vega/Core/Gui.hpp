#pragma once

#include <string>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <Vega/Core/Core.hpp>

namespace Vega {
  class Gui final {
  SINGLETON(Gui)

  private:
    explicit Gui() = default;

    explicit Gui(const std::string &version) {
      IMGUI_CHECKVERSION();

      ImGui::CreateContext();
      ImGui::StyleColorsDark();

      ImGuiIO &io = ImGui::GetIO();

      ImGuiStyle &style = ImGui::GetStyle();
      style.WindowBorderSize = 0.f;

      ImGui_ImplGlfw_InitForOpenGL(&Window::Get().GetNativeWindow(), true);
      ImGui_ImplOpenGL3_Init(std::string{"#version " + version}.c_str());
    }

    virtual ~Gui() {
      ImGui_ImplOpenGL3_Shutdown();
      ImGui_ImplGlfw_Shutdown();

      ImGui::DestroyContext();
    }

  public:
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