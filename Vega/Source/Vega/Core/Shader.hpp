#pragma once

#include <Vega/Std.hpp>
#include <Vega/Vendor.hpp>

#include <Vega/Core/Core.hpp>
#include <Vega/Core/Filesystem.hpp>

#include <Vega/Debug/Core.hpp>

namespace Vega::Core {
  class Shader {
  public:
    explicit Shader(fs::path vertexPath, fs::path fragmentPath);

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

    fs::path mVertex;
    fs::path mFragment;

    unsigned int mVid;
    unsigned int mFid;
    unsigned int mPid;
  };
}