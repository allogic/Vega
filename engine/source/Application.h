#ifndef APPLICATION_H
#define APPLICATION_H

#define BIND_EVENT_FN(function) std::bind(&Application::function, this, std::placeholders::_1)

namespace vega {
  Application *Make();

  class Application {
    friend Input;

  public:
    explicit Application(unsigned int width, unsigned int height, const std::string &title, unsigned int antialiasing) :
        mWidth(width),
        mHeight(height) {
      if (!glfwInit()) throw std::runtime_error("Unable to initialize glfw");

      glfwWindowHint(GLFW_SAMPLES, static_cast<int>(antialiasing));
      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
      glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
      glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

      mWindow = glfwCreateWindow(static_cast<int>(width), static_cast<int>(height), title.c_str(), nullptr, nullptr);

      if (!mWindow) throw std::runtime_error("Unable to create window");

      glfwMakeContextCurrent(mWindow);

      if (!gladLoadGL()) throw std::runtime_error("Unable to initialize glad");

      sInstance = this;
    }

    virtual ~Application() = default;

    [[nodiscard]] inline GLFWwindow &Window() const { return *mWindow; }

    [[nodiscard]] inline unsigned int Width() const { return mWidth; }
    [[nodiscard]] inline unsigned int Height() const { return mHeight; }

    [[nodiscard]] inline float AspectRatio() const {
      return static_cast<float>(mWidth) / static_cast<float>(mHeight);
    }

    inline void PushLayer(Layer *layer) {
      mLayers.push_back(layer);
    }

    void Run() {
      while (mRunning) {
        auto time = static_cast<float>(glfwGetTime());

        Timestep ts(time - mPrevTime);

        mPrevTime = time;

        for (auto layer : mLayers) layer->OnUpdate(ts);
      }

      glfwDestroyWindow(mWindow);

      glfwTerminate();
    }

    void Stop() {
      mRunning = false;
    }

  private:
    unsigned int mWidth, mHeight;

    float mPrevTime = 0.f;

    bool mRunning = true;

    GLFWwindow *mWindow;

    std::vector<Layer *> mLayers;

  private:
    static Application *sInstance;
  };
}

#endif