#pragma once

#include <Vega/Std.hpp>

#include <Vega/Core/Core.hpp>

namespace Vega::Core::Filesystem {
  static const std::string RootPath = VEGA_ROOT_PATH;
  static const std::string CppCompiler = VEGA_CPP_COMPILER;

  static bool Read(std::string &data, const fs::path &root) {
    VEGA_RUNTIME_ERROR(!fs::exists(root) || fs::is_directory(root), "Invalid root path");

    std::ifstream file(root);

    std::stringstream ss;
    std::string line;

    if (!file.is_open()) return false;

    while (getline(file, line))
      ss << line << std::endl;

    file.close();

    data = ss.str();

    return true;
  }

  static bool Write(const std::string &data, const fs::path &root) {
    VEGA_RUNTIME_ERROR(!fs::exists(root) || fs::is_directory(root), "Invalid root path");

    std::ofstream file(root);

    if (!file.is_open()) return false;

    file << data;

    file.close();

    return true;
  }

  template<typename Constraint>
  static void RecursiveConstraintFor(
      const fs::path &root,
      const Constraint &constraint,
      const std::function<void(const fs::path &)> &predicate) {
    VEGA_RUNTIME_ERROR(!fs::is_directory(root), "Invalid root path");

    fs::path currentPath;

    bool checkCurrentFolder = false;
    bool isValidShader = true;

    for (const auto &path : fs::directory_iterator(root)) {
      if (fs::is_directory(path)) RecursiveConstraintFor(path, constraint, predicate);
      else {
        currentPath = path;

        checkCurrentFolder = true;
        if (!constraint(path)) isValidShader = false;
      }
    }

    if (checkCurrentFolder && isValidShader) predicate(currentPath);
  }

  struct ExtensionConstraint {
    const std::vector<std::string> &Extensions;

    bool operator()(const fs::path &root) const {
      const std::string fileExtension = root.extension().string();

      return std::find(std::cbegin(Extensions), std::cend(Extensions), fileExtension) != std::cend(Extensions);
    }
  };

  struct NameExtensionConstraint {
    const std::vector<std::string> &Extensions;

    bool operator()(const fs::path &root) const {
      const std::string fileName = root.stem().string() + root.extension().string();

      return std::find(std::cbegin(Extensions), std::cend(Extensions), fileName) != std::cend(Extensions);
    }
  };
}