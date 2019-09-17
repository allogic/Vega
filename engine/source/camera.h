#ifndef CAMERA_H
#define CAMERA_H

namespace vega {
  class Camera {
  public:
    explicit Camera(const glm::fvec3 &position) : _position(position) {}

    virtual void update() = 0;

    [[nodiscard]] inline glm::fmat4 projection(float aspect_ratio) const {
      return glm::perspective(glm::radians(45.f), aspect_ratio, 0.1f, 1000.f);
    }

    [[nodiscard]] inline glm::fmat4 view() const {
      return glm::lookAt(_position, _position + _front, _up);
    }

  protected:
    glm::fvec3 _position;

    glm::fvec3 _front{0.f, 0.f, 1.f}, _up{0.f, 1.f, 0.f};
  };

  namespace camera {
    class OrbitCamera final : public Camera {
    public:
      explicit OrbitCamera(const glm::fvec3 &position) : Camera(position) {}

      void update() override {
        //cursor_velocity.x += cursor_x *

        glm::fquat rotation{glm::fvec3(cursor.x, cursor.y, 0.f)};

        _position = rotation * glm::fvec3{0.f, 0.f, -10.f};
      }
    };
  }
}

#endif