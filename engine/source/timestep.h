#ifndef TIMESTEP_H
#define TIMESTEP_H

namespace vega {
  class Timestep final {
  public:
    explicit Timestep(float time = 0.f) : _time(time) {}

    float operator()() const { return _time; }

    [[nodiscard]] inline float seconds() const { return _time; }
    [[nodiscard]] inline float milliseconds() const { return _time * 1000.f; }

  private:
    float _time;
  };
}

#endif