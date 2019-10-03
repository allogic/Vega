#pragma once

#include <string>

#include <glad/glad.h>

namespace Vega {
  class Shader {
  public:
    explicit Shader(const std::string &vertexSource, const std::string &fragmentSource);

    virtual ~Shader();

    inline void Bind() const { glUseProgram(mPid); }

  private:
    unsigned int mPid;
  };
}