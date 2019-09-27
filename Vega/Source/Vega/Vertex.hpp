#ifndef VEGA_VERTEX_HPP
#define VEGA_VERTEX_HPP

#include <glm/glm.hpp>

namespace Vega {
  class Vertex final {
  public:
    explicit Vertex(const glm::fvec3 &position, const glm::fvec3 &normal) : mPosition(position), mNormal(normal) {}

    inline glm::fvec3 &Position() { return mPosition; }
    inline glm::fvec3 &Normal() { return mNormal; }

    inline static std::size_t PositionStride() { return sizeof(Vertex) + sizeof(glm::fvec3); }

  private:
    glm::fvec3 mPosition;
    glm::fvec3 mNormal;
  };
}

#endif