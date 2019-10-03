#ifndef VEGA_ENTITYMANAGER_HPP
#define VEGA_ENTITYMANAGER_HPP

#include <entityx/entityx.h>

#include <Vega/Core/Core.hpp>

namespace Vega {
  class EntityManager final : protected entityx::EntityX {
  SINGLETON(EntityManager)

  public:
    inline entityx::EventManager &Events() { return events; }
    inline entityx::SystemManager &Systems() { return systems; }
    inline entityx::EntityManager &Entites() { return entities; }

  private:
    explicit EntityManager() = default;
  };
}

#endif