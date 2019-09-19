#ifndef INPUT_H
#define INPUT_H

#include "Application.h"

namespace vega {
  class VEGA_API Input final {
  public:
    explicit Input() = default;

    [[nodiscard]] inline static bool IsKeyPressed(int keycode) {
      auto &window = Application::sInstance->Window();
      auto state = glfwGetKey(&window, keycode);

      return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    [[nodiscard]] inline static bool IsMousePressed(int button) {
      auto &window = Application::sInstance->Window();
      auto state = glfwGetMouseButton(&window, button);

      return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    [[nodiscard]] inline static std::pair<float, float> GetMousePosition() {
      auto &window = Application::sInstance->Window();
      double x, y;

      glfwGetCursorPos(&window, &x, &y);

      return {static_cast<float>(x), static_cast<float>(y)};
    }

    [[nodiscard]] inline static float GetMouseX() { return GetMousePosition().first; }
    [[nodiscard]] inline static float GetMouseY() { return GetMousePosition().second; }
  };
}

#endif