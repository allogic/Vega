#ifndef SHADER_H
#define SHADER_H

namespace vega {
  static void compile(unsigned int sid, const std::string &source, bool debug) {
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

  class Shader {
  public:
    explicit Shader(const std::string &vertex_source, const std::string &fragment_source, bool debug = false) :
        _pid(glCreateProgram()) {
      unsigned int vid = glCreateShader(GL_VERTEX_SHADER);
      unsigned int fid = glCreateShader(GL_FRAGMENT_SHADER);

      compile(vid, vertex_source, debug);
      compile(fid, fragment_source, debug);

      glAttachShader(_pid, vid);
      glAttachShader(_pid, fid);

      glLinkProgram(_pid);

      glDetachShader(_pid, vid);
      glDetachShader(_pid, fid);

      glDeleteShader(_pid);
      glDeleteShader(fid);
    };

    virtual ~Shader() {
      glDeleteProgram(_pid);
    }

    inline void bind() const {
      glUseProgram(_pid);
    }

    inline void fmat4(const std::string &name, const glm::fmat4 &matrix) const {
      glUniformMatrix4fv(glGetUniformLocation(_pid, name.c_str()), 1, GL_FALSE, &matrix[0][0]);
    }

  private:
    unsigned int _pid;
  };

  namespace shader {
    class DebugShader final : public Shader {
    public:
      DebugShader() : Shader(R"vertex(
#version 430 core

layout (location = 0) in vec3 l_position;
layout (location = 1) in vec3 l_normal;

out vec3 position;
out vec3 normal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main() {
  position = vec3(model * vec4(l_position, 1.0));
  normal = mat3(model) * l_normal;

  gl_Position = projection * view * vec4(position, 1.0);
}
      )vertex", R"fragment(
#version 430 core

in vec3 position;
in vec3 normal;

out vec4 color;

void main() {
  color = vec4(normal, 1.0);
}
      )fragment") {}
    };
  }
}

#endif