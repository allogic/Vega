#pragma once

#include <Vega/Std.hpp>

#include <Vega/Vendor/Glfw.hpp>
#include <Vega/Vendor/Imgui.hpp>
#include <Vega/Vendor/Glm.hpp>

#include <Vega/Core/Core.hpp>
#include <Vega/Core/Loader/ConfigLoader.hpp>

namespace Vega::Core {
  class Window;

  class Application final {
    friend class Callback;

  public:
    explicit Application(int width, int height, Window *window);

    virtual ~Application() = default;

  public:
    void Run();

  public:
    inline void WindowSize(const glm::ivec2 &size) { mWindowSize = size; }
    inline void MousePosition(const glm::fvec2 &position) { mMousePosition = position; }
    inline void MouseScroll(const glm::fvec2 &scroll) { mMouseScoll = scroll; }

  private:
    Window *mWindow;

    bool mRunning = true;

    glm::ivec2 mWindowSize;
    glm::fvec2 mMousePosition{};
    glm::fvec2 mMouseScoll{};

    unsigned int mMaxFramesPerSecond = 60;
    unsigned int mMaxUpdatesPerSecond = 1;

    double mFPSLimit = 1.0f / mMaxFramesPerSecond;
    double mUPSLimit = 1.0f / mMaxUpdatesPerSecond;

    Loader::ConfigLoader mConfigLoader;
  };
}