#include <Vega/Tmp/Model.hpp>

Vega::Model::Model(const std::string &file) {
  Assimp::Importer importer;

  const aiScene *scene = importer.ReadFile(file, aiProcess_Triangulate |
                                                 aiProcess_FlipUVs |
                                                 aiProcess_CalcTangentSpace);

  assert((!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) && "Failed loading model");

  for (unsigned int i = 0; i < scene->mNumMeshes; i++)
    mMeshes.emplace_back(Convert(scene->mMeshes[i], scene));
}

void Vega::Model::Bind() const {
  for (const auto mesh : mMeshes) mesh.Bind();
}