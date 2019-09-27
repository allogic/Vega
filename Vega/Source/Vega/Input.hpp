#ifndef VEGA_INPUT_HPP
#define VEGA_INPUT_HPP

namespace Vega {
  class Input final {
  public:
    explicit Input() = delete;

    virtual ~Input() = default;

    /*
    static bool IsKeyPressed(int key) {
      auto &window = Application::Get().Window();
      auto state = glfwGetKey(&window, key);

      return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    static bool IsMousePressed(int button) {
      auto &window = Application::Get().Window();
      auto state = glfwGetMouseButton(&window, button);

      return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    static std::pair<float, float> GetMousePosition() {
      auto &window = Application::Get().Window();
      double x, y;

      glfwGetCursorPos(&window, &x, &y);

      return {static_cast<float>(x), static_cast<float>(y)};
    }

    static float GetMouseX() { return GetMousePosition().first; }
    static float GetMouseY() { return GetMousePosition().second; }
     */
  };
}

#endif