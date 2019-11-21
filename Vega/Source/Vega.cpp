//TODO Create API interface
//TODO Abstract config loader
//TODO Rewrite main
//TODO Rewrite logging
//TODO Remove vega source dir

#include <Core/Window.hpp>
#include <Core/Ui.hpp>
#include <Core/Application.hpp>
#include <Core/Callback.hpp>

#include <Utility/Args.hpp>
#include <Utility/Settings.hpp>

int main(int argc, char **argv) {
  if (Vega::Utility::Args::Handle(argc, argv)) {
    if (GLFWwindow *window = Vega::Core::Window::Init(); window) {
      if (Vega::Core::Ui::Init(window)) {
        Vega::Core::Application application{window};

        application.Run();

        Vega::Core::Ui::Destroy();
      }

      Vega::Core::Window::Destroy(window);
    }
  }

  Vega::Utility::Settings::Instance().Delete();

  return 0;
}