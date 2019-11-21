#ifndef UI_HPP
#define UI_HPP

#pragma once

#include <Std.hpp>

#include <imgui.h>
#include <examples/imgui_impl_glfw.h>
#include <examples/imgui_impl_opengl3.h>

#include <Utility/Settings.hpp>

namespace Vega::Core::Ui {
  static bool Init(GLFWwindow *window) {
    auto &settings = Vega::Utility::Settings::Instance();

    if (!IMGUI_CHECKVERSION()) {
      VEGA_ERROR("Failed to initialize ui")
      return false;
    }

    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    std::string glslVersion = std::string{"#version " + std::to_string(settings.Get<int>("glsl-version"))};

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glslVersion.c_str());

    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGuiStyle &style = ImGui::GetStyle();
    style.WindowBorderSize = 0.f;

    return true;
  }

  static void Destroy() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();

    ImGui::DestroyContext();
  }
}

#endif