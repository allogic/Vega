#pragma once

#include <imgui.h>

#include <Vega/Debug/ShaderEditor.hpp>
#include <Vega/Debug/ResourceHierarchy.hpp>

namespace Vega::Debug {
  static void Draw() {
    static bool showShaderEditor = false;

    if (ImGui::BeginMainMenuBar()) {
      if (ImGui::BeginMenu("Shaders")) {
        if (ImGui::MenuItem("Open Editor")) showShaderEditor = true;
        ImGui::EndMenu();
      }
    }

    ImGui::EndMainMenuBar();

    if (showShaderEditor) DrawShaderEditor(showShaderEditor);

    DrawResourceHierarchy();
  }
}