#pragma once

#include <string>
#include <fstream>
#include <sstream>

#include <glad/glad.h>

#include <Vega/Core/ShaderUtilities.hpp>

namespace Vega::Debug {
  static void DrawShaderEditor(bool &open) {
    static std::string mVertexShaderSource;
    static std::string mFragmentShaderSource;

    if (!ImGui::Begin("Shader Editor", &open)) {
      ImGui::End();
      return;
    }

    if (ImGui::Button("Load")) {
      Shader::Utility::Load(mVertexShaderSource, "/home/michael/Downloads/Vega/Sandbox/Shader/DemoShader.vert");
      Shader::Utility::Load(mFragmentShaderSource, "/home/michael/Downloads/Vega/Sandbox/Shader/DemoShader.frag");
    }

    ImGui::SameLine();

    if (ImGui::Button("Save")) {
      Shader::Utility::Write(mVertexShaderSource, "/home/michael/Downloads/Vega/Sandbox/Shader/DemoShader.vert");
      Shader::Utility::Write(mFragmentShaderSource, "/home/michael/Downloads/Vega/Sandbox/Shader/DemoShader.frag");
    }

    ImGui::SameLine();

    if (ImGui::Button("Compile")) {
      //ShaderCompiler::Compile(mShaderSource);
    }

    ImGui::Text("Vertex Shader");
    ImGui::Text("Fragment Shader");

    static auto flags = ImGuiInputTextFlags_AllowTabInput | ImGuiInputTextFlags_CtrlEnterForNewLine;

    ImGui::InputTextMultiline("", &mVertexShaderSource[0], mVertexShaderSource.size(),
                              ImVec2(ImGui::GetContentRegionAvail().x, 500), flags);

    //ImGui::InputTextMultiline("", &mFragmentShaderSource[0], mFragmentShaderSource.size(),
    //                          ImVec2(ImGui::GetContentRegionAvail().x * 0.5f, 500), flags);

    ImGui::End();
  }
}