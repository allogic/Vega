#ifndef GUI_HPP
#define GUI_HPP

#pragma once

#include <Std.hpp>

#include <imgui.h>
#include <examples/imgui_impl_glfw.h>
#include <examples/imgui_impl_opengl3.h>

#include <Utility/Settings.hpp>

namespace Vega::Core {
  /*class Gui final {
  public:
    explicit Gui(Window *window) : mWindow(window) {
      auto &settings = Vega::Utility::Settings::Instance();

      IMGUI_CHECKVERSION();

      ImGui::CreateContext();
      ImGui::StyleColorsDark();

      std::string glslVersion = std::string{"#version " + std::to_string(settings.Get<int>("glsl-version"))};

      ImGui_ImplGlfw_InitForOpenGL(mWindow->mWindow, true);
      ImGui_ImplOpenGL3_Init(glslVersion.c_str());

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
  };*/
}

#endif