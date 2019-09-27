#include <Sandbox/DemoLayer.hpp>

void Demo::CustomLayer::OnUpdate(double deltaTime) {}

void Demo::CustomLayer::OnDraw() {}

void Demo::CustomLayer::OnImGui(double deltaTime) {
  ImGui::Text("Demo");
}