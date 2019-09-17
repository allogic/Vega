#ifndef MODEL_H
#define MODEL_H

namespace vega {
  static Mesh convert(const aiMesh *mesh, const aiScene *scene) {
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

  class Model {
  public:
    explicit Model(const std::string &file) {
      Assimp::Importer importer;

      const aiScene *scene = importer.ReadFile(file, aiProcess_Triangulate |
                                                     aiProcess_FlipUVs |
                                                     aiProcess_CalcTangentSpace);

      if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        throw std::runtime_error("can not load model");

      for (unsigned int i = 0; i < scene->mNumMeshes; i++)
        _meshes.emplace_back(convert(scene->mMeshes[i], scene));
    }

    inline void bind() const {
      for (const auto mesh : _meshes) mesh.bind();
    }

  private:
    std::vector<Mesh> _meshes;
  };
}

#endif