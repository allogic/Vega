#ifndef MESH_H
#define MESH_H

namespace vega {
  class Mesh {
  public:
    explicit Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices) :
        _size(indices.size()) {
      glGenVertexArrays(1, &_vao);

      glGenBuffers(1, &_vbo);
      glGenBuffers(1, &_ebo);

      glBindVertexArray(_vao);

      glBindBuffer(GL_ARRAY_BUFFER, _vbo);
      glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

      glEnableVertexAttribArray(0);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);

      glEnableVertexAttribArray(1);
      glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                            reinterpret_cast<void *>(Vertex::position_offset()));

      glBindVertexArray(0);
    }

    void bind() const {
      glBindVertexArray(_vao);
      glDrawElements(GL_TRIANGLES, _size, GL_UNSIGNED_INT, nullptr);
    }

  private:
    unsigned int _size;
    unsigned int _vao = 0, _vbo = 0, _ebo = 0;
  };
}

#endif