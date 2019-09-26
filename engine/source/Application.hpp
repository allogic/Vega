#ifndef VEGA_APPLICATION_HPP
#define VEGA_APPLICATION_HPP

namespace Vega {
  Application *Make();

  class Application {
  public:
    explicit Application(unsigned int width, unsigned int height,
                         const std::string &title, const std::string &glsl,
                         unsigned int major, unsigned int minor,
                         unsigned int antialiasing) :
        mWidth(width),
        mHeight(height) {
      if (!glfwInit()) throw std::runtime_error("Unable to initialize glfw");

      glfwWindowHint(GLFW_SAMPLES, static_cast<int>(antialiasing));
      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, static_cast<int>(major));
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, static_cast<int>(minor));
      glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
      glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

      mWindow = glfwCreateWindow(static_cast<int>(width), static_cast<int>(height), title.c_str(), nullptr, nullptr);

      assert(mWindow && "Unable to create window");

      glfwMakeContextCurrent(mWindow);

      if (!gladLoadGL()) throw std::runtime_error("Unable to initialize glad");

      IMGUI_CHECKVERSION();

      ImGui::CreateContext();
      ImGui::StyleColorsDark();

      ImGui_ImplGlfw_InitForOpenGL(mWindow, true);

      std::string glslVersion = "#version " + glsl;

      ImGui_ImplOpenGL3_Init(glslVersion.c_str());
    }

    virtual ~Application() {
      for (auto layer : mLayers) delete layer;

      ImGui_ImplOpenGL3_Shutdown();
      ImGui_ImplGlfw_Shutdown();

      ImGui::DestroyContext();

      glfwDestroyWindow(mWindow);
      glfwTerminate();
    };

    [[nodiscard]] inline GLFWwindow &Window() const { return *mWindow; }

    [[nodiscard]] inline unsigned int Width() const { return mWidth; }
    [[nodiscard]] inline unsigned int Height() const { return mHeight; }

    [[nodiscard]] inline float AspectRatio() const {
      return static_cast<float>(mWidth) / static_cast<float>(mHeight);
    }

    inline void PushLayer(Layer *layer) { mLayers.push_back(layer); }

    void Run() {
      double lastUpdateTime = 0;
      double lastFrameTime = 0;

      while (!glfwWindowShouldClose(mWindow)) {
        double now = glfwGetTime();
        double deltaTime = now - lastUpdateTime;

        glfwPollEvents();

        for (auto layer : mLayers) layer->OnUpdate(deltaTime);

        if ((now - lastFrameTime) >= mFPSLimit) {
          glClearColor(0.f, 0.f, 0.f, 1.f);
          glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

          for (auto layer : mLayers) layer->OnDraw();

          ImGui_ImplOpenGL3_NewFrame();
          ImGui_ImplGlfw_NewFrame();

          ImGui::NewFrame();
          for (auto layer : mLayers) layer->OnImgui(deltaTime);
          ImGui::EndFrame();

          ImGui::Render();
          ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

          glfwSwapBuffers(mWindow);

          lastFrameTime = now;
        }

        lastUpdateTime = now;
      }
    }

  private:
    unsigned int mWidth;
    unsigned int mHeight;

    unsigned int mMaxFPS = 60;

    double mFPSLimit = 1.0 / mMaxFPS;

    GLFWwindow *mWindow;

    std::vector<Layer *> mLayers;
  };
}

#endif