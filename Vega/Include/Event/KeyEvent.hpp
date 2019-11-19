#ifndef KEYEVENT_HPP
#define KEYEVENT_HPP

#pragma once

#include <Event/Event.hpp>

namespace Vega::Event {
  class KeyEvent final : public Event {
  public:
    unsigned int Key;

    explicit KeyEvent(unsigned int key) :
        Event(EventCategory::KeyEvent),
        Key(key) {}
  };
}

#endif