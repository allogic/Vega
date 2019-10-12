#pragma once

#include <Vega/Std.hpp>
#include <Vega/Platform.hpp>

#include <Vega/Core/Module.hpp>
#include <Vega/Core/Filesystem.hpp>

#include <Vega/Debug/Core.hpp>

namespace Vega::Core {
  class SharedObject final {
  public:
    using create_t = Module *();

  public:
    SharedObject(fs::path input, fs::path output);

    virtual ~SharedObject();

  public:
    void Load();
    void Unload();

    void DebugReloadIfChanged();

    [[nodiscard]] inline Module &Instance() const { return *mInstance; }

  private:
    bool Compile();
    void Bind();
    void Unbind();

  private:
    std::chrono::high_resolution_clock::time_point mLastWriteTime;

    fs::path mInput;
    fs::path mOutput;

    void *mDlHandle = nullptr;

    create_t *mCreate = nullptr;

    Module *mInstance = nullptr;
  };
}