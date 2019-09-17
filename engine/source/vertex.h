#ifndef VERTEX_H
#define VERTEX_H

namespace vega {
  class Vertex final {
  public:
    explicit Vertex(const glm::fvec3 &position, const glm::fvec3 &normal) : _position(position), _normal(normal) {}

    [[nodiscard]] inline glm::fvec3 &position() { return _position; }
    [[nodiscard]] inline glm::fvec3 &normal() { return _normal; }

    [[nodiscard]] static inline std::size_t position_offset() { return sizeof(Vertex) + sizeof(float) * 3; }

  private:
    glm::fvec3 _position, _normal;
  };
}

#endif