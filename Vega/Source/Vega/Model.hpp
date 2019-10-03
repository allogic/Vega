#ifndef VEGA_MODEL_HPP
#define VEGA_MODEL_HPP

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <glm/glm.hpp>

#include <Vega/Mesh.hpp>

namespace Vega {
  static Mesh Convert(const aiMesh *mesh, const aiScene *scene) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
      vertices.emplace_back(glm::fvec3{mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z},
                            glm::fvec3{mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z});

    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
      for (unsigned int j = 0; j < mesh->mFaces[i].mNumIndices; j++)
        indices.emplace_back(mesh->mFaces[i].mIndices[j]);

    return Mesh{vertices, indices};
  }

  class Model final {
  public:
    explicit Model(const std::string &file);

    inline void Bind() const;

  private:
    std::vector<Mesh> mMeshes;
  };
}

#endif