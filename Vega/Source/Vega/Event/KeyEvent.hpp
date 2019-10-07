#pragma once

#include <Vega/Event/Event.hpp>

namespace Vega {
  class KeyEvent final : public Event {
  public:
    unsigned int Key;

    explicit KeyEvent(unsigned int key) : Key(key) {}
  };
}