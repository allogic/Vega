#include <Vega/Core/Shader.hpp>

Vega::Shader::Shader(const std::filesystem::path &vertexPath, const std::filesystem::path &fragmentPath) :
    mVertexPath(vertexPath), mFragmentPath(fragmentPath) {
  mVid = glCreateShader(GL_VERTEX_SHADER);
  mFid = glCreateShader(GL_FRAGMENT_SHADER);

  glDetachShader(mPid, mVid);
  glDetachShader(mPid, mFid);

  mPid = glCreateProgram();
}

Vega::Shader::~Shader() {
  glDeleteShader(mVid);
  glDeleteShader(mFid);

  glDeleteProgram(mPid);
}

bool Vega::Shader::Load() {
  if (!Io::Read(mVertexSource, mVertexPath)) return false;
  if (!Io::Read(mFragmentShader, mFragmentPath)) return false;

  return true;
}

bool Vega::Shader::Save() {
  if (!Io::Write(mVertexSource, mVertexPath)) return false;
  if (!Io::Write(mFragmentShader, mFragmentPath)) return false;

  return true;
}

bool Vega::Shader::Compile(std::string &shaderError) {
  if (!Compile(mVid, mVertexSource, shaderError)) return false;
  if (!Compile(mFid, mFragmentShader, shaderError)) return false;

  glAttachShader(mPid, mVid);
  glAttachShader(mPid, mFid);

  glLinkProgram(mPid);

  return true;
}

bool Vega::Shader::Compile(unsigned int sid, const std::string &shaderSource, std::string &shaderError) const {
  const char *ptr = shaderSource.c_str();

  glShaderSource(sid, 1, &ptr, nullptr);
  glCompileShader(sid);

  int info, size;

  glGetShaderiv(sid, GL_COMPILE_STATUS, &info);
  glGetShaderiv(sid, GL_INFO_LOG_LENGTH, &size);

  if (size > 0) {
    char msg[size];

    glGetShaderInfoLog(sid, size, nullptr, msg);

    shaderError = msg;

    return false;
  }

  return true;
}
