#ifndef VEGA_APPLICATION_HPP
#define VEGA_APPLICATION_HPP

#include <Vega/Core/Core.hpp>
#include <Vega/Core/Window.hpp>
#include <Vega/EntityManager.hpp>

#include <Vega/Core/Layer.hpp>
#include <Vega/Core/LayerStack.hpp>

#include <Vega/Debug/DebugMenu.hpp>
#include <Vega/Debug/ShaderEditor.hpp>

namespace Vega {
  class Application {
  public:
    explicit Application(const std::string &title = "Vega",
                         unsigned int width = 1280,
                         unsigned int height = 720,
                         unsigned int antialiasing = 0);

    virtual ~Application() = default;

    void Run();

    inline void PushLayer(Layer *layer) { mLayerStack.Push(layer); }
    inline void PushOverlay(Layer *layer) { mLayerStack.Pop(layer); }

  private:
    unsigned int mMaxFPS = 60;

    double mFPSLimit = 1.0 / mMaxFPS;

    LayerStack mLayerStack;
  };

  extern Application *Make();
}

#endif