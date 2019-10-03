#include <Vega/Core/Shader.hpp>

Vega::Shader::Shader(const std::string &vertexSource, const std::string &fragmentSource) {
  mPid = glCreateProgram();

  unsigned int vid = glCreateShader(GL_VERTEX_SHADER);
  unsigned int fid = glCreateShader(GL_FRAGMENT_SHADER);

  //Compile(vid, vertexSource);
  //Compile(fid, fragmentSource);

  glAttachShader(mPid, vid);
  glAttachShader(mPid, fid);

  glLinkProgram(mPid);

  glDetachShader(mPid, vid);
  glDetachShader(mPid, fid);

  glDeleteShader(vid);
  glDeleteShader(fid);

  glUseProgram(0);
}

Vega::Shader::~Shader() {
  glDeleteProgram(mPid);
}
