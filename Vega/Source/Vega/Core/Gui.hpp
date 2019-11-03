#pragma once

#include <Vega/Std.hpp>

#include <Vega/Vendor/Imgui.hpp>

#include <Vega/Utility/Settings.hpp>

namespace Vega::Core {
  class Gui final {
  public:
    explicit Gui(Window *window) : mWindow(window) {
      IMGUI_CHECKVERSION();

      ImGui::CreateContext();
      ImGui::StyleColorsDark();

      ImGui_ImplGlfw_InitForOpenGL(mWindow->mWindow, true);
      ImGui_ImplOpenGL3_Init(std::string{"#version " + CONFIG_GET(std::string, "glsl-version")}.c_str());

      ImGuiIO &io = ImGui::GetIO();
      io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

      ImGuiStyle &style = ImGui::GetStyle();
      style.WindowBorderSize = 0.f;
    }

    virtual ~Gui() {
      ImGui_ImplOpenGL3_Shutdown();
      ImGui_ImplGlfw_Shutdown();

      ImGui::DestroyContext();
    }

  private:
    Window *mWindow;
  };
}