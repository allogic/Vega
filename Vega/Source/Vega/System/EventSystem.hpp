#ifndef VEGA_EVENTSYSTEM_HPP
#define VEGA_EVENTSYSTEM_HPP

#include <entityx/entityx.h>

namespace Vega {
  class EventSystem : public entityx::System<EventSystem>, public entityx::Receiver<EventSystem> {
  public:
    void configure(entityx::EventManager &events) override {

    }

    void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {

    }
  };
}

#endif