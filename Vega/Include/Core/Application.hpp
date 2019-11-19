#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#pragma once

#include <Std.hpp>

#include <GLFW/glfw3.h>

#include <imgui.h>
#include <examples/imgui_impl_glfw.h>
#include <examples/imgui_impl_opengl3.h>

#include <glm/glm.hpp>

#include <Core/Core.hpp>
#include <Core/Loader/ConfigLoader.hpp>

namespace Vega::Core {
  class Application final {
    friend class Callback;

  public:
    explicit Application() = default;

    virtual ~Application() = default;

  public:
    void Run();

  public:
    inline void WindowSize(const glm::ivec2 &size) { mWindowSize = size; }
    inline void MousePosition(const glm::fvec2 &position) { mMousePosition = position; }
    inline void MouseScroll(const glm::fvec2 &scroll) { mMouseScoll = scroll; }

  private:
    bool mRunning = true;

    glm::ivec2 mWindowSize{};
    glm::fvec2 mMousePosition{};
    glm::fvec2 mMouseScoll{};

    unsigned int mMaxFramesPerSecond = 60;
    unsigned int mMaxUpdatesPerSecond = 1;

    double mFPSLimit = 1.0f / mMaxFramesPerSecond;
    double mUPSLimit = 1.0f / mMaxUpdatesPerSecond;

    Loader::ConfigLoader mConfigLoader{};
  };
}

#endif