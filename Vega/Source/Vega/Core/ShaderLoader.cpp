#include <Vega/Core/ShaderLoader.hpp>

Vega::Core::ShaderLoader::ShaderLoader(const std::filesystem::path &root) {
  Filesystem::RecursiveConstraintFor(root, Filesystem::ExtensionConstraint{{".vert", ".frag"}},
                                     [&](const std::filesystem::path &path) {
                                       const std::string shader =
                                           path.parent_path().string() + "/" + path.filename().stem().string();

                                       mShaders.push_back(
                                           std::make_unique<Shader>(shader + ".vert", shader + ".frag"));
                                     });
}

void Vega::Core::ShaderLoader::DebugReloadIfChanged() {
  for (auto &shader : mShaders) shader->DebugReloadIfChanged();
}
