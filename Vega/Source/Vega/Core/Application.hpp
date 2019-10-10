#pragma once

#include <Vega/Std.hpp>
#include <Vega/Vendor.hpp>

#include <Vega/Core/Core.hpp>
#include <Vega/Core/ModuleLoader.hpp>
#include <Vega/Core/ShaderLoader.hpp>

#include <Vega/Event/WindowEvent.hpp>
#include <Vega/Event/MouseEvent.hpp>
#include <Vega/Event/KeyEvent.hpp>

#include <Vega/Debug/DebugMenu.hpp>
#include <Vega/Debug/ShaderEditor.hpp>

namespace Vega::Core {
  class Application {
    using EventCallback = std::function<void(const Event::Event &)>;

  public:
    explicit Application(const std::string &title = "Vega",
                         unsigned int width = 1280,
                         unsigned int height = 720,
                         unsigned int antialiasing = 0);

    virtual ~Application();

    void Run();

    virtual void OnUpdate() {}
    virtual void OnDraw() const {}
    virtual void OnEvent(const Event::Event &event);
    virtual void OnGui() {}

    [[nodiscard]] inline glm::ivec2 WindowSize() const { return mWindowSize; }
    [[nodiscard]] inline glm::fvec2 MouseScroll() const { return mMouseScoll; }
    [[nodiscard]] inline glm::fvec2 MousePosition() const { return mMousePosition; }

    [[nodiscard]] bool KeyPressed(const Event::Event &event, unsigned int key) const;
    [[nodiscard]] bool KeyHeld(const Event::Event &event, unsigned int key) const;
    [[nodiscard]] bool KeyReleased(const Event::Event &event, unsigned int key) const;

    [[nodiscard]] bool MousePressed(const Event::Event &event, unsigned int key) const;
    [[nodiscard]] bool MouseHeld(const Event::Event &event, unsigned int key) const;
    [[nodiscard]] bool MouseReleased(const Event::Event &event, unsigned int key) const;

  private:
    bool OnWindowClose(const Event::Event &event);
    bool OnWindowResize(const Event::Event &event);

    bool OnMousePosition(const Event::Event &event);
    bool OnMouseScroll(const Event::Event &event);

  private:
    GLFWwindow *mWindow = nullptr;

    EventCallback mEventCallback;

    bool mRunning = true;

    glm::ivec2 mWindowSize;
    glm::fvec2 mMouseScoll{};
    glm::fvec2 mMousePosition{};

    unsigned int mMaxFPS = 60;

    double mFPSLimit = 1.0 / mMaxFPS;
  };

  Application *Make();
}