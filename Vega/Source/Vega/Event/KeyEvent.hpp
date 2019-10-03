#ifndef VEGA_KEYEVENT_HPP
#define VEGA_KEYEVENT_HPP

namespace Vega {
  class KeyEvent final {
  public:
    unsigned int Key;
    unsigned int Action;

    explicit KeyEvent(unsigned int key, unsigned int action) : Key(key), Action(action) {}
  };
}

#endif