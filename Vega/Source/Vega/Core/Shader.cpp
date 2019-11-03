#include <Vega/Core/Shader.hpp>

/*Vega::Core::Shader::Shader(std::experimental::filesystem::path vertex, std::experimental::filesystem::path fragment) :
    mVertex(vertex),
    mFragment(fragment),
    mLastWriteTimeVertex(std::experimental::filesystem::last_write_time(vertex)),
    mLastWriteTimeFragment(std::experimental::filesystem::last_write_time(fragment)) {
  Load();
}

Vega::Core::Shader::~Shader() {
  Unload();
}

void Vega::Core::Shader::Load() {
  mVid = glCreateShader(GL_VERTEX_SHADER);
  mFid = glCreateShader(GL_FRAGMENT_SHADER);

  Compile();

  glAttachShader(mPid, mVid);
  glAttachShader(mPid, mFid);

  glLinkProgram(mPid);

  glDetachShader(mPid, mVid);
  glDetachShader(mPid, mFid);

  mPid = glCreateProgram();
}

void Vega::Core::Shader::Unload() {
  glDeleteShader(mVid);
  glDeleteShader(mFid);

  glDeleteProgram(mPid);
}

void Vega::Core::Shader::DebugReloadIfChanged() {
  auto currentWriteTimeVertex = std::experimental::filesystem::last_write_time(mVertex);
  auto currentWriteTimeFragment = std::experimental::filesystem::last_write_time(mFragment);

  if (mLastWriteTimeVertex >= currentWriteTimeVertex && mLastWriteTimeFragment >= currentWriteTimeFragment)
    return;

  mLastWriteTimeVertex = currentWriteTimeVertex;
  mLastWriteTimeFragment = currentWriteTimeFragment;

  Unload();
  Load();
}

void Vega::Core::Shader::Compile() {
  std::string vertexSource;
  Utility::Io::Read(vertexSource, mVertex);

  std::string fragmentSource;
  Utility::Io::Read(fragmentSource, mFragment);

  std::string shaderError;

  VEGA_INFO("Compiling shader %s %s", mVertex.filename().c_str(), mFragment.filename().c_str());

  VEGA_INFO("===========%s COMPILING===========", "BEGIN")
  if (!CompileShader(mVid, vertexSource, shaderError)) std::cout << shaderError << std::endl;
  if (!CompileShader(mFid, fragmentSource, shaderError)) std::cout << shaderError << std::endl;
  VEGA_INFO("===========%s COMPILING===========", " END ")

  VEGA_INFO("Compiling shader VertexId: %d FragmentId: %d", mVid, mFid);
}

bool Vega::Core::Shader::CompileShader(unsigned int sid, const std::string &shaderSource, std::string &shaderError) {
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
}*/