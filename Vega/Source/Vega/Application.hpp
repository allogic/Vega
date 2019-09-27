#ifndef VEGA_APPLICATION_HPP
#define VEGA_APPLICATION_HPP

#include <string>

#include <Vega/Window.hpp>
#include <Vega/Layer.hpp>
#include <Vega/LayerStack.hpp>

#include <Vega/ImGui/ImGuiLayer.hpp>

namespace Vega {
  class Application {
  public:
    explicit Application(const std::string &title = "Vega",
                         unsigned int width = 1280,
                         unsigned int height = 720,
                         unsigned int major = 4,
                         unsigned int minor = 3,
                         unsigned int antialiasing = 0) {
      assert(!sInstance && "Application already exists");
      sInstance = this;

      mWindow = new Window(title, width, height, major, minor, antialiasing);

      //mImGuiLayer = new ImGuiLayer();
      //PushLayer(mImGuiLayer);
    }

    virtual ~Application() = default;

    inline void PushLayer(Layer *layer) { mLayerStack.Push(layer); }
    inline void PopLayer(Layer *layer) { mLayerStack.Pop(layer); }

    [[nodiscard]] inline static Application &GetApplication() { return *sInstance; }

    [[nodiscard]] inline Window &GetWindow() { return *mWindow; }

    void Run() {
      double lastUpdateTime = 0;
      double lastFrameTime = 0;

      while (!glfwWindowShouldClose(&mWindow->GetNativeWindow())) {
        double now = glfwGetTime();
        double deltaTime = now - lastUpdateTime;

        glfwPollEvents();

        for (auto layer : mLayerStack) layer->OnUpdate(deltaTime);

        if ((now - lastFrameTime) >= mFPSLimit) {
          glClearColor(0.f, 0.f, 0.f, 1.f);
          glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

          for (auto layer : mLayerStack) layer->OnDraw();

          //mImGuiLayer->Begin();
          for (auto layer : mLayerStack) layer->OnImGui(deltaTime);
          //mImGuiLayer->End();

          glfwSwapBuffers(&mWindow->GetNativeWindow());

          lastFrameTime = now;
        }

        lastUpdateTime = now;
      }
    }

  private:
    unsigned int mMaxFPS = 60;

    double mFPSLimit = 1.0 / mMaxFPS;

    Window *mWindow;

    ImGuiLayer *mImGuiLayer;

    LayerStack mLayerStack;

  private:
    inline static Application *sInstance = nullptr;
  };
}

#endif