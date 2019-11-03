#include <Vega.hpp>

int main(int argc, char **argv) {
  std::vector<std::string> args = {argv + 1, argv + argc};

  namespace Parser = Vega::Utility::Parser;

  CONFIG_SET("sketch-path", Parser::Match(args, "", "--sketch-path", "-sp"))
  CONFIG_SET("gl-major", std::stoi(Parser::Match(args, "4", "--gl-major", "-gma")));
  CONFIG_SET("gl-minor", std::stoi(Parser::Match(args, "3", "--gl-minor", "-gmi")));
  CONFIG_SET("glsl-version", Parser::Match(args, "430", "--glsl-version", "-gv"));
  CONFIG_SET("title", Parser::Match(args, "Vega", "--title", "-t"));
  CONFIG_SET("antialiasing", std::stoi(Parser::Match(args, "0", "--antialiasing", "-aa")));
  CONFIG_SET("cpp-compiler", Parser::Match(args, "", "--cpp-compiler", "-cmp"));
  CONFIG_SET("vega-source-path", Parser::Match(args, "", "--vega-source-path", "-vsp"));

  VEGA_RUNTIME_ERROR(CONFIG_GET(std::string, "sketch-path").empty(), "Invalid sketch path specified");
  VEGA_RUNTIME_ERROR(CONFIG_GET(std::string, "cpp-compiler").empty(), "Invalid cpp compiler specified");
  VEGA_RUNTIME_ERROR(CONFIG_GET(std::string, "vega-source-path").empty(), "Invalid vega source path specified");

  int width = std::stoi(Parser::Match(args, "600", "--width", "-w"));
  int height = std::stoi(Parser::Match(args, "600", "--height", "-h"));

  auto *window = new Vega::Core::Window(width, height);
  auto *gui = new Vega::Core::Gui(window);
  auto *application = new Vega::Core::Application(width, height, window);
  auto *callback = new Vega::Core::Callback(window, application);

  application->Run();

  delete callback;
  delete application;
  delete gui;
  delete window;

  Vega::Utility::Settings::Instance().Delete();
}