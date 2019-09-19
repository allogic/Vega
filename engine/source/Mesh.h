#ifndef MESH_H
#define MESH_H

namespace vega {
  class VEGA_API Mesh {
  public:
    explicit Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices) :
        mSize(indices.size()) {
      glGenVertexArrays(1, &mVao);

      glGenBuffers(1, &mVbo);
      glGenBuffers(1, &mEbo);

      glBindVertexArray(mVao);

      glBindBuffer(GL_ARRAY_BUFFER, mVbo);
      glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEbo);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

      glEnableVertexAttribArray(0);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);

      glEnableVertexAttribArray(1);
      glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                            reinterpret_cast<void *>(Vertex::PositionStride()));

      glBindVertexArray(0);
    }

    void Bind() const {
      glBindVertexArray(mVao);
      glDrawElements(GL_TRIANGLES, mSize, GL_UNSIGNED_INT, nullptr);
    }

  private:
    unsigned int mSize;
    unsigned int mVao = 0, mVbo = 0, mEbo = 0;
  };
}

#endif