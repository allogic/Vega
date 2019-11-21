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

#include <Event/Event.hpp>
#include <Event/WindowEvent.hpp>
#include <Event/MouseEvent.hpp>
#include <Event/KeyEvent.hpp>

namespace Vega::Core {
  class Application final {
    using EventCallback = void (Application::*)(const Event::Event &event);

  public:
    explicit Application(GLFWwindow *window);

  public:
    void Run();

  public:
    bool KeyPressed(const Event::Event &event, unsigned int key) const;
    bool KeyHeld(const Event::Event &event, unsigned int key) const;
    bool KeyReleased(const Event::Event &event, unsigned int key) const;

    bool MousePressed(const Event::Event &event, unsigned int key) const;
    bool MouseHeld(const Event::Event &event, unsigned int key) const;
    bool MouseReleased(const Event::Event &event, unsigned int key) const;

  private:
    void OnEvent(const Event::Event &event);

  private:
    bool OnWindowClose(const Event::Event &event) const;
    bool OnWindowResize(const Event::Event &event) const;
    bool OnMousePosition(const Event::Event &event) const;
    bool OnMouseScroll(const Event::Event &event) const;

  private:
    EventCallback mCallback;

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