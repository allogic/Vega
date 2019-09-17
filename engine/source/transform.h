#ifndef TRANSFORM_H
#define TRANSFORM_H

namespace vega {
  class Transform {
  public:
    explicit Transform(
        const glm::fvec3 &position = {0.f, 0.f, 0.f},
        const glm::fvec3 &rotation = {0.f, 0.f, 0.f},
        const glm::fvec3 &scale = {1.f, 1.f, 1.f}) :
        _position(position),
        _rotation(rotation),
        _scale(scale) {}

    [[nodiscard]] inline glm::fvec3 &position() { return _position; }
    [[nodiscard]] inline glm::fvec3 &rotation() { return _rotation; }
    [[nodiscard]] inline glm::fvec3 &scale() { return _scale; }

    [[nodiscard]] glm::fmat4 model() const {
      glm::mat4 model{1.f};

      glm::translate(model, _position);

      glm::rotate(model, _rotation.x, glm::fvec3{1.f, 0.f, 0.f});
      glm::rotate(model, _rotation.y, glm::fvec3{0.f, 1.f, 0.f});
      glm::rotate(model, _rotation.z, glm::fvec3{0.f, 0.f, 1.f});

      glm::scale(model, _scale);

      return model;
    }

  private:
    glm::fvec3 _position, _rotation, _scale;
  };
}

#endif