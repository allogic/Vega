#ifndef SHAREDOBJECT_HPP
#define SHAREDOBJECT_HPP

#pragma once

#include <Std.hpp>
#include <Platform.hpp>

#include <Core/Module.hpp>

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

#endif