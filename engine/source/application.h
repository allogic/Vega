#ifndef APPLICATION_H
#define APPLICATION_H

namespace vega {
  static void cursor_position_callback(GLFWwindow *window, double x, double y) { cursor = {x, y}; }
  static void scroll_wheel_callback(GLFWwindow *window, double x, double y) { scroll = {x, y}; }
  static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {}

  extern Application *make();

  class Application {
  public:
    explicit Application(unsigned int width, unsigned int height, const std::string &title, unsigned int antialiasing) :
        _width(width),
        _height(height) {
      if (!glfwInit()) throw std::runtime_error("Unable to initialize glfw");

      glfwWindowHint(GLFW_SAMPLES, static_cast<int>(antialiasing));
      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
      glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
      glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

      _window = glfwCreateWindow(static_cast<int>(width), static_cast<int>(height), title.c_str(), nullptr, nullptr);

      glfwSetCursorPosCallback(_window, cursor_position_callback);
      glfwSetScrollCallback(_window, scroll_wheel_callback);
      glfwSetMouseButtonCallback(_window, mouse_button_callback);

      if (!_window) throw std::runtime_error("Unable to create window");

      glfwMakeContextCurrent(_window);

      if (!gladLoadGL()) throw std::runtime_error("Unable to initialize glad");
    }

    virtual ~Application() = default;

    [[nodiscard]] inline GLFWwindow *window() const { return _window; }

    [[nodiscard]] inline unsigned int width() const { return _width; }
    [[nodiscard]] inline unsigned int height() const { return _height; }

    [[nodiscard]] inline float aspect_ratio() const {
      return static_cast<float>(_width) / static_cast<float>(_height);
    }

    void run() {
      while (!glfwWindowShouldClose(_window)) {
        auto time = static_cast<float>(glfwGetTime());

        Timestep timestep(time - _prevTime);

        _prevTime = time;

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glCullFace(GL_FRONT_AND_BACK);

        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwSwapBuffers(_window);
        glfwPollEvents();
      }

      glfwDestroyWindow(_window);

      glfwTerminate();
    }

  private:
    unsigned int _width, _height;

    float _prevTime = 0.f;

    GLFWwindow *_window;
  };
}

#endif