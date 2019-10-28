#pragma once

#include <Vega/Std.hpp>
#include <Vega/Platform.hpp>

#include <Vega/Core/Module.hpp>

#include <Vega/Utility/Io.hpp>

namespace Vega::Core {
  class SharedObject final {
  public:
    using CreateModule = Module *();

  public:
    SharedObject(std::experimental::filesystem::path input, std::experimental::filesystem::path output);

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

    std::experimental::filesystem::path mInput;
    std::experimental::filesystem::path mOutput;

    void *mDlHandle = nullptr;

    CreateModule *mCreate = nullptr;

    Module *mInstance = nullptr;
  };
}