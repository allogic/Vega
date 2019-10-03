#ifndef VEGA_ENTRYPOINT_HPP
#define VEGA_ENTRYPOINT_HPP

#include <Vega/Core/Window.hpp>
#include <Vega/Core/Gui.hpp>
#include <Vega/EntityManager.hpp>

int main(int argc, char **argv) {
  auto app = Vega::Make();

  app->Run();

  delete app;

  //Vega::EntityManager::Del();

#ifdef VEGA_ENABLE_GUI
  Vega::Gui::Del();
#endif

  Vega::Window::Del();
}

#endif