#pragma once

// cmake todos
// TODO create public/private include interfaces

// format todos
// TODO prefix function params with t
// TODO move implementation into source files
// TODO move functions/variables into public/private blocks

// structure todos
// TODO runtime string converter macro
// TODO redo resource loader
// TODO dockable gui with fixed windows and props/styles
// TODO make gui console & logging
// TODO convert singleton with member ref variables
// TODO implement GLFW event callbacks

#include <Vega/Core/Application.hpp>

int main(int argc, char **argv) {
  auto app = Vega::Core::Make();

  app->Run();

  delete app;
}