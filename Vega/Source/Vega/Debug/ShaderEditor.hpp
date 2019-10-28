#pragma once

#include <string>
#include <fstream>
#include <sstream>

//#include <glad/glad.h>

#include <Vega/Core/Shader.hpp>

namespace Vega::Debug {
  static void DrawShaderEditor(bool &open) {
    static std::string mVertexShaderSource;
    static std::string mFragmentShaderSource;

    if (!ImGui::Begin("Shaders Editor", &open)) {
      ImGui::End();
      return;
    }

    if (ImGui::Button("Load")) {
      //Shaders::Load(mVertexShaderSource, "/home/michael/Downloads/Vega/Sandbox/Shaders/Demo.vert");
      //Shaders::Load(mFragmentShaderSource, "/home/michael/Downloads/Vega/Sandbox/Shaders/Demo.frag");
    }

    ImGui::SameLine();

    if (ImGui::Button("Save")) {
      //Shaders::Write(mVertexShaderSource, "/home/michael/Downloads/Vega/Sandbox/Shaders/Demo.vert");
      //Shaders::Write(mFragmentShaderSource, "/home/michael/Downloads/Vega/Sandbox/Shaders/Demo.frag");
    }

    ImGui::SameLine();

    if (ImGui::Button("Compile")) {
      //ShaderCompiler::Compile(mShaderSource);
    }

    ImGui::Text("Vertex Shaders");
    ImGui::Text("Fragment Shaders");

    static auto flags = ImGuiInputTextFlags_AllowTabInput | ImGuiInputTextFlags_CtrlEnterForNewLine;

    ImGui::InputTextMultiline("", &mVertexShaderSource[0], mVertexShaderSource.size(),
                              ImVec2(ImGui::GetContentRegionAvail().x, 500), flags);

    //ImGui::InputTextMultiline("", &mFragmentShaderSource[0], mFragmentShaderSource.size(),
    //                          ImVec2(ImGui::GetContentRegionAvail().x * 0.5f, 500), flags);

    ImGui::End();
  }
}