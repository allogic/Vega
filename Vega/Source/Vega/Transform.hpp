#ifndef VEGA_TRANSFORM_HPP
#define VEGA_TRANSFORM_HPP

namespace Vega {
  class Transform {
  public:
    explicit Transform(
        const glm::fvec3 &position = {0.f, 0.f, 0.f},
        const glm::fvec3 &rotation = {0.f, 0.f, 0.f},
        const glm::fvec3 &scale = {1.f, 1.f, 1.f}) :
        mPosition(position),
        mRotation(rotation),
        mScale(scale) {}

    [[nodiscard]] inline glm::fvec3 &Position() { return mPosition; }
    [[nodiscard]] inline glm::fvec3 &Rotation() { return mRotation; }
    [[nodiscard]] inline glm::fvec3 &Scale() { return mScale; }

    [[nodiscard]] glm::fmat4 Model() const {
      glm::mat4 model{1.f};

      glm::translate(model, mPosition);

      glm::rotate(model, mRotation.x, glm::fvec3{1.f, 0.f, 0.f});
      glm::rotate(model, mRotation.y, glm::fvec3{0.f, 1.f, 0.f});
      glm::rotate(model, mRotation.z, glm::fvec3{0.f, 0.f, 1.f});

      glm::scale(model, mScale);

      return model;
    }

  private:
    glm::fvec3 mPosition;
    glm::fvec3 mRotation;
    glm::fvec3 mScale;
  };
}

#endif