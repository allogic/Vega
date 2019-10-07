#pragma once

#include <string>
#include <filesystem>

#include <glad/glad.h>

#include <Vega/Core/Io.hpp>

namespace Vega {
  class Shader {
  public:
    explicit Shader(const std::filesystem::path &vertexPath, const std::filesystem::path &fragmentPath);

    virtual ~Shader();

    bool Load();
    bool Save();

    bool Compile(std::string &shaderError);

    inline void Bind() const { glUseProgram(mPid); }

  private:
    bool Compile(unsigned int sid, const std::string &shaderSource, std::string &shaderError) const;

  private:
    const std::filesystem::path &mVertexPath;
    const std::filesystem::path &mFragmentPath;

    std::string mVertexSource;
    std::string mFragmentShader;

    unsigned int mVid;
    unsigned int mFid;
    unsigned int mPid;
  };
}