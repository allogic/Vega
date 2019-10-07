#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include <Vega/Core/Core.hpp>
#include <Vega/Core/Window.hpp>
#include <Vega/Core/Gui.hpp>
#include <Vega/Core/ResourceManager.hpp>

#include <Vega/Event/Event.hpp>
#include <Vega/Event/WindowEvent.hpp>

#include <Vega/Debug/DebugMenu.hpp>
#include <Vega/Debug/ShaderEditor.hpp>

namespace Vega {
  class Application {
  public:
    explicit Application(const std::string &title = "Vega",
                         unsigned int width = 1280,
                         unsigned int height = 720,
                         unsigned int antialiasing = 0);

    virtual ~Application();

    void Run();

    virtual void OnUpdate() {}
    virtual void OnDraw() const {}
    virtual void OnEvent(const Event &event);
    virtual void OnGui() {}

    [[nodiscard]] inline glm::ivec2 GetWindowSize() const { return mWindowSize; }
    [[nodiscard]] inline glm::fvec2 GetMouseScroll() const { return mMouseScoll; }
    [[nodiscard]] inline glm::fvec2 GetMousePosition() const { return mMousePosition; }

    [[nodiscard]] bool KeyPressed(const Event &event, unsigned int key) const;
    [[nodiscard]] bool KeyHeld(const Event &event, unsigned int key) const;
    [[nodiscard]] bool KeyReleased(const Event &event, unsigned int key) const;

    [[nodiscard]] bool MousePressed(const Event &event, unsigned int key) const;
    [[nodiscard]] bool MouseHeld(const Event &event, unsigned int key) const;
    [[nodiscard]] bool MouseReleased(const Event &event, unsigned int key) const;

  private:
    void WindowClose(const Event &event);
    void WindowResize(const Event &event);

    void MouseScroll(const Event &event);
    void MousePosition(const Event &event);

  private:
    bool mRunning = true;

    unsigned int mWidth;
    unsigned int mHeight;

    glm::ivec2 mWindowSize;
    glm::fvec2 mMouseScoll;
    glm::fvec2 mMousePosition;

    unsigned int mMaxFPS = 60;

    double mFPSLimit = 1.0 / mMaxFPS;
  };

  extern Application *Make();
}