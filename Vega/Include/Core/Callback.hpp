#ifndef CALLBACK_HPP
#define CALLBACK_HPP

#pragma once

#include <Std.hpp>

#include <GLFW/glfw3.h>

#include <Core/Application.hpp>

#include <Event/Event.hpp>
#include <Event/WindowEvent.hpp>
#include <Event/MouseEvent.hpp>
#include <Event/KeyEvent.hpp>

namespace Vega::Core {
  class Callback final {
    using EventCallback = std::function<void(const Event::Event &)>;

  public:
    explicit Callback();

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
    EventCallback mEventCallback{};
  };
}

#endif