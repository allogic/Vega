#ifndef TIMESTEP_H
#define TIMESTEP_H

namespace vega {
  class VEGA_API Timestep final {
  public:
    explicit Timestep(float time = 0.f) : mTime(time) {}

    float operator()() const { return mTime; }

    [[nodiscard]] inline float Seconds() const { return mTime; }
    [[nodiscard]] inline float Milliseconds() const { return mTime * 1000.f; }

  private:
    float mTime;
  };
}

#endif