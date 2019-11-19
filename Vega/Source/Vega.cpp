//TODO Create API interface
//TODO Abstract config loader
//TODO Rewrite main
//TODO Rewrite logging
//TODO Remove vega source dir

#include <Std.hpp>

#include <cxxopts.hpp>

#include <Core/Core.hpp>
#include <Core/Window.hpp>
#include <Core/Gui.hpp>
#include <Core/Application.hpp>
#include <Core/Callback.hpp>

#include <Utility/Settings.hpp>

template<typename T>
void TrySetArg(const cxxopts::ParseResult &args, const std::string &key, bool &error) {
  if (args.count(key) == 1) {
    Vega::Utility::Settings::Instance().Set(key, args[key].as<T>());
    return;
  }

  VEGA_INFO("Missing or too many arguments {0}", key)
  error = true;
}

int main(int argc, char **argv) {
  cxxopts::Options options{"Vega", "Vega Engine"};

  options.add_option("", "w", "width", "Window width", cxxopts::value<int>(), "");
  options.add_option("", "h", "height", "Window height", cxxopts::value<int>(), "");
  options.add_option("", "t", "title", "Window title", cxxopts::value<std::string>(), "");
  options.add_option("", "gma", "gl-major", "OpenGL major version", cxxopts::value<int>(), "");
  options.add_option("", "gmi", "gl-minor", "OpenGL minor version", cxxopts::value<int>(), "");
  options.add_option("", "gv", "glsl-version", "GLSL version", cxxopts::value<int>(), "");
  options.add_option("", "aa", "antialiasing", "Antialiasing", cxxopts::value<int>(), "");
  options.add_option("", "sp", "sketch-path", "Sketch path", cxxopts::value<std::string>(), "");
  options.add_option("", "ccp", "cpp-compiler", "C++ compiler path", cxxopts::value<std::string>(), "");
  options.add_option("", "vip", "vega-include-path", "Vega API path", cxxopts::value<std::string>(), "");

  auto args = options.parse(argc, argv);

  bool error = false;

  TrySetArg<int>(args, "width", error);
  TrySetArg<int>(args, "height", error);
  TrySetArg<std::string>(args, "title", error);
  TrySetArg<int>(args, "gl-major", error);
  TrySetArg<int>(args, "gl-minor", error);
  TrySetArg<int>(args, "glsl-version", error);
  TrySetArg<int>(args, "antialiasing", error);
  TrySetArg<std::string>(args, "sketch-path", error);
  TrySetArg<std::string>(args, "cpp-compiler", error);
  TrySetArg<std::string>(args, "vega-include-path", error);

  if (!error) {
    Vega::Core::Window::Create();

    Vega::Core::Window::Destroy();

    /*auto *window = new Vega::Core::Window(width, height);
    auto *gui = new Vega::Core::Gui(window);
    auto *application = new Vega::Core::Application(width, height, window);
    auto *callback = new Vega::Core::Callback(window, application);

    application->Run();

    delete callback;
    delete application;
    delete gui;
    delete window;*/
  }

  Vega::Utility::Settings::Instance().Delete();
}