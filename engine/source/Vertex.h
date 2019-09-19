#ifndef VERTEX_H
#define VERTEX_H

namespace vega {
  class VEGA_API Vertex final {
  public:
    explicit Vertex(const glm::fvec3 &position, const glm::fvec3 &normal) : mPosition(position), mNormal(normal) {}

    [[nodiscard]] inline glm::fvec3 &Position() { return mPosition; }
    [[nodiscard]] inline glm::fvec3 &Normal() { return mNormal; }

    [[nodiscard]] static inline std::size_t PositionStride() { return sizeof(Vertex) + sizeof(glm::fvec3); }

  private:
    glm::fvec3 mPosition, mNormal;
  };
}

#endif