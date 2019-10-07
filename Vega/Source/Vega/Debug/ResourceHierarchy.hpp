#pragma once

namespace Vega::Debug {
  static void DrawResourceHierarchy() {
    ImGui::Begin("test");

    if (ImGui::TreeNode("Basic trees"))
    {
      for (int i = 0; i < 5; i++)
      {
        // Use SetNextItemOpen() so set the default state of a node to be open.
        // We could also use TreeNodeEx() with the ImGuiTreeNodeFlags_DefaultOpen flag to achieve the same thing!
        if (i == 0)
          ImGui::SetNextItemOpen(true, ImGuiCond_Once);

        if (ImGui::TreeNode((void*)(intptr_t)i, "Child %d", i))
        {
          ImGui::Text("blah blah");
          ImGui::SameLine();
          if (ImGui::SmallButton("button")) {};
          ImGui::TreePop();
        }
      }
      ImGui::TreePop();
    }

    ImGui::SameLine(ImGui::GetWindowWidth());

    if (ImGui::TreeNode("Hierarchy")) {
      for (unsigned int i = 0; i < 10; i++) {
        if (ImGui::TreeNode(reinterpret_cast<void *>(i), "Child %d", i)) {
          ImGui::Text("Vertex");

          ImGui::SameLine();

          if (ImGui::Button("Open")) {

          }

          ImGui::TreePop();
        }

        i++;
      }

      ImGui::TreePop();
    }

    ImGui::End();
  }
}