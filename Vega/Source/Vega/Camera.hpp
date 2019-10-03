#ifndef VEGA_CAMERA_HPP
#define VEGA_CAMERA_HPP

namespace Vega {
  class Camera {
  public:
    explicit Camera(const glm::fvec3 &position) : mPosition(position) {}

    inline glm::fmat4 Projection(float aspectRatio) const {
      return glm::perspective(glm::radians(45.f), aspectRatio, 0.1f, 1000.f);
    }

    inline glm::fmat4 View() const {
      return glm::lookAt(mPosition, mPosition + mFront, mUp);
    }

  protected:
    glm::fvec3 mPosition;

    glm::fvec3 mFront = {0.f, 0.f, 1.f};
    glm::fvec3 mUp = {0.f, 1.f, 0.f};
  };
}

#endif