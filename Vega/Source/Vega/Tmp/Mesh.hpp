#pragma once

#include <Vega/Std.hpp>

#include <Vega/Vendor/Glad.hpp>
#include <Vega/Vendor/Glm.hpp>

#include <Vega/Tmp/Vertex.hpp>

namespace Vega {
  class Mesh final {
  public:
    explicit Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices);

    void Bind() const;

  private:
    unsigned int mSize;

    unsigned int mVao = 0;
    unsigned int mVbo = 0;
    unsigned int mEbo = 0;
  };
}