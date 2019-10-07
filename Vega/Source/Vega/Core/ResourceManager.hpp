#pragma once

#include <string>
#include <filesystem>
#include <vector>
#include <memory>
#include <map>

#include <Vega/Core/Core.hpp>
#include <Vega/Core/Shader.hpp>

namespace Vega {
  class ResourceManager {
  SINGLETON(ResourceManager)

  public:
    inline const std::shared_ptr<Shader> &GetShader(const std::string &name) const {
      auto it = mResource.find(name);

      VEGA_RUNTIME_ERROR(it != std::end(mResource), "Failed finding resource");

      return it->second;
    }

    inline const std::vector<std::string> &Keys() const { return mKeys; }

  private:
    explicit ResourceManager() = default;

    explicit ResourceManager(const std::string &rootPath) {
      LoadShaders({rootPath + "/Shader"});
    };

    void LoadShaders(const std::filesystem::path &path) {
      VEGA_RUNTIME_ERROR(!std::filesystem::exists(path) || !std::filesystem::is_directory(path), "Invalid shader path");

      for (auto &entry : std::filesystem::directory_iterator(path)) {
        if (!entry.is_directory()) continue;

        std::filesystem::path shaderFilePath = entry.path();
        shaderFilePath /= entry.path().filename();
        std::string shaderFileName = shaderFilePath.string();

        std::filesystem::path vertexShaderPath = {shaderFileName + ".vert"};
        std::filesystem::path fragmentShaderPath = {shaderFileName + ".frag"};

        bool foundVertexShader = std::filesystem::exists(vertexShaderPath);
        bool foundFragmentShader = std::filesystem::exists(fragmentShaderPath);

        if (!foundVertexShader || !foundFragmentShader) continue;

        auto shader = std::make_shared<Shader>(vertexShaderPath, fragmentShaderPath);

        std::string shaderError;

        shader->Load();
        shader->Compile(shaderError);

        mKeys.push_back(entry.path().filename());

        mResource.insert(std::make_pair(entry.path().filename(), shader));
      }
    }

  private:
    std::vector<std::string> mKeys;

    std::map<std::string, std::shared_ptr<Shader>> mResource;
  };
}