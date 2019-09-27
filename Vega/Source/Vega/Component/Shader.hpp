#ifndef VEGA_SHADER_HPP
#define VEGA_SHADER_HPP

#include <glad/glad.h>

#include <iostream>
#include <string>

#include <Vega/Core.hpp>

namespace Vega {
  static void Compile(unsigned int sid, const std::string &source, bool debug) {
    const char *ptr = source.c_str();

    glShaderSource(sid, 1, &ptr, nullptr);
    glCompileShader(sid);

    if (!debug) return;

    int info, size;

    glGetShaderiv(sid, GL_COMPILE_STATUS, &info);
    glGetShaderiv(sid, GL_INFO_LOG_LENGTH, &size);

    if (size > 0) {
      char msg[size];

      glGetShaderInfoLog(sid, size, nullptr, msg);

      std::cout << msg << std::endl;
    }
  }

  class VEGA_API Shader {
  public:
    explicit Shader(const std::string &vertexSource, const std::string &fragmentSource, bool debug = false) :
        mPid(glCreateProgram()) {
      unsigned int vid = glCreateShader(GL_VERTEX_SHADER);
      unsigned int fid = glCreateShader(GL_FRAGMENT_SHADER);

      Compile(vid, vertexSource, debug);
      Compile(fid, fragmentSource, debug);

      glAttachShader(mPid, vid);
      glAttachShader(mPid, fid);

      glLinkProgram(mPid);

      glDetachShader(mPid, vid);
      glDetachShader(mPid, fid);

      glDeleteShader(vid);
      glDeleteShader(fid);

      glUseProgram(0);
    };

    virtual ~Shader() {
      glDeleteProgram(mPid);
    }

    inline void Bind() const {
      glUseProgram(mPid);
    }

  private:
    unsigned int mPid;
  };
}

#endif