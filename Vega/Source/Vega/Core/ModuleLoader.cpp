#include <Vega/Core/ModuleLoader.hpp>

Vega::Core::ModuleLoader::ModuleLoader(const fs::path &root) {
  Filesystem::RecursiveConstraintFor(root, Filesystem::NameExtensionConstraint{{".cpp"}},
                                     [&](const fs::path &path) {
                                       const std::string module =
                                           path.parent_path().string() + "/" + path.filename().stem().string();

                                       mSharedObjects.push_back(
                                           std::make_unique<SharedObject>(module + ".cpp", module + ".so"));
                                     });
}

void Vega::Core::ModuleLoader::OnUpdate(float deltaTime) {
  for (auto &sharedObject : mSharedObjects) sharedObject->Instance().OnUpdate(deltaTime);
}

void Vega::Core::ModuleLoader::DebugReloadIfChanged() {
  for (auto &sharedObject : mSharedObjects) sharedObject->DebugReloadIfChanged();
}