#pragma once

#include <Vega/Std.hpp>
#include <Vega/Platform.hpp>

#include <Vega/Core/Module.hpp>

/*namespace Vega::Core {
  class SharedObject final {
    using CreateModule = Module *();

  public:
    SharedObject();

    virtual ~SharedObject();

    inline Module &Instance() const { return *mInstance; }

  private:
    void *mDlHandle = nullptr;

    CreateModule *mCreate = nullptr;

    Module *mInstance = nullptr;
  };
}*/