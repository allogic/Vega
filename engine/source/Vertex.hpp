#ifndef VEGA_VERTEX_HPP
#define VEGA_VERTEX_HPP

namespace Vega {
  class VEGA_API Vertex final {
  public:
    explicit Vertex(const glm::fvec3 &position, const glm::fvec3 &normal) : mPosition(position), mNormal(normal) {}

    [[nodiscard]] inline glm::fvec3 &Position() { return mPosition; }
    [[nodiscard]] inline glm::fvec3 &Normal() { return mNormal; }

    [[nodiscard]] static inline std::size_t PositionStride() { return sizeof(Vertex) + sizeof(glm::fvec3); }

  private:
    glm::fvec3 mPosition;
    glm::fvec3 mNormal;
  };
}

#endif