#pragma once

#include <string>

#include <glad/glad.h>

namespace Vega::Shader::Utility {
  static bool Compile(unsigned int id, const char *shaderSource, std::string &shaderError) {
    glShaderSource(id, 1, &shaderSource, nullptr);
    glCompileShader(id);

    int info, size;

    glGetShaderiv(id, GL_COMPILE_STATUS, &info);
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &size);

    if (size > 0) {
      char msg[size];

      glGetShaderInfoLog(id, size, nullptr, msg);

      shaderError = msg;

      return false;
    }

    return true;
  }

  static bool Load(std::string &shaderSource, const std::string &shaderPath) {
    std::ifstream file(shaderPath);

    std::stringstream ss;
    std::string line;

    if (!file.is_open()) return false;

    while (getline(file, line))
      ss << line << std::endl;

    file.close();

    shaderSource = ss.str();

    return true;
  }

  static bool Write(const std::string &shaderSource, const std::string &shaderPath) {
    std::ofstream file(shaderPath);

    if (!file.is_open()) return false;

    file << shaderSource;

    file.close();

    return true;
  }
}