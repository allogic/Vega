#pragma once

#include <Vega/Std.hpp>

#include <Vega/Core/Core.hpp>

#include <Vega/Utility/Io.hpp>

/*namespace Vega::Core {
  class Shader {
  public:
    explicit Shader(std::experimental::filesystem::path vertexPath, std::experimental::filesystem::path fragmentPath);

    virtual ~Shader();

  public:
    void Load();
    void Unload();

    void DebugReloadIfChanged();

    inline void Bind() const { glUseProgram(mPid); }
    inline void Unbind() const { glUseProgram(0); }

  private:
    void Compile();

    bool CompileShader(unsigned int sid, const std::string &shaderSource, std::string &shaderError);

  private:
    std::chrono::high_resolution_clock::time_point mLastWriteTimeVertex;
    std::chrono::high_resolution_clock::time_point mLastWriteTimeFragment;

    std::experimental::filesystem::path mVertex;
    std::experimental::filesystem::path mFragment;

    unsigned int mVid;
    unsigned int mFid;
    unsigned int mPid;
  };
}*/