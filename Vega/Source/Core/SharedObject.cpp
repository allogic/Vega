#include <Core/SharedObject.hpp>

/*Vega::Core::SharedObject::SharedObject(std::experimental::filesystem::path input,
                                       std::experimental::filesystem::path output) :
    mInput(input),
    mOutput(output),
    mLastWriteTime(std::experimental::filesystem::last_write_time(input)) {
  Load();
}

Vega::Core::SharedObject::~SharedObject() {
  Unload();
}

void Vega::Core::SharedObject::Load() {
  Bind();
}

void Vega::Core::SharedObject::Unload() {
  Unbind();
}

void Vega::Core::SharedObject::DebugReloadIfChanged() {
  auto currWriteTime = std::experimental::filesystem::last_write_time(mInput);
  std::cout << "reloaded" << std::endl;
  if (mLastWriteTime >= currWriteTime) return;

  mLastWriteTime = currWriteTime;

  Unbind();
  Compile();
  Bind();
}

bool Vega::Core::SharedObject::Compile() {
  const std::string cmd = Utility::Io::CppCompiler + " -shared -fPIC -I" +
                          Utility::Io::VegaSourcePath + "Vega/Source/ " +
                          mInput.string() + " -o " + mOutput.string();

  VEGA_INFO("Compiling module %s: %s", mInput.filename().c_str(), cmd.c_str())

  VEGA_INFO("===========%s COMPILING===========", "BEGIN")
  int result = std::system(cmd.c_str());
  VEGA_INFO("===========%s COMPILING===========", " END ")

  VEGA_INFO("Compiling module %s: %d", mInput.filename().c_str(), result)

  return result == 0;
  return true;
}

void Vega::Core::SharedObject::Bind() {
  char *error = nullptr;

  mDlHandle = dlopen(mOutput.c_str(), RTLD_LAZY);
  error = dlerror();

  if (!mDlHandle) VEGA_ERROR("Failed to get dynamic link handle %s", error)

  dlerror(); // Reset errors

  mCreate = reinterpret_cast<CreateModule *>(dlsym(mDlHandle, "Create"));
  error = dlerror();

  if (error) {
    VEGA_ERROR("Failed to load symbol: %s", error)

    Unbind();
  }

  mInstance = mCreate();
}

void Vega::Core::SharedObject::Unbind() {
  delete mInstance;

  mInstance = nullptr;
  mCreate = nullptr;

  if (mDlHandle) {
    dlclose(mDlHandle);

    mDlHandle = nullptr;
  }
}*/