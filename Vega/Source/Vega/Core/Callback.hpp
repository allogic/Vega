#pragma once

#include <Vega/Std.hpp>

#include <Vega/Vendor/Glfw.hpp>

#include <Vega/Core/Application.hpp>

#include <Vega/Event/Event.hpp>
#include <Vega/Event/WindowEvent.hpp>
#include <Vega/Event/MouseEvent.hpp>
#include <Vega/Event/KeyEvent.hpp>

namespace Vega::Core {
  class Window;

  class Callback final {
    using EventCallback = std::function<void(const Event::Event &)>;

  public:
    explicit Callback(Window *window, Application *application);

    virtual ~Callback() = default;

  private:
    void OnEvent(const Event::Event &event);

    bool OnWindowClose(const Event::Event &event);
    bool OnWindowResize(const Event::Event &event);

    bool OnMousePosition(const Event::Event &event);
    bool OnMouseScroll(const Event::Event &event);

  public:
    [[nodiscard]] bool KeyPressed(const Event::Event &event, unsigned int key) const;
    [[nodiscard]] bool KeyHeld(const Event::Event &event, unsigned int key) const;
    [[nodiscard]] bool KeyReleased(const Event::Event &event, unsigned int key) const;

    [[nodiscard]] bool MousePressed(const Event::Event &event, unsigned int key) const;
    [[nodiscard]] bool MouseHeld(const Event::Event &event, unsigned int key) const;
    [[nodiscard]] bool MouseReleased(const Event::Event &event, unsigned int key) const;

  private:
    Window *mWindow;
    Application *mApplication;

    EventCallback mEventCallback;
  };
}