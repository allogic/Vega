#pragma once

// format todos
// TODO prefix function params with t
// TODO move implementation into source files
// TODO move functions/variables into public/private blocks

// structure todos
// TODO make gui console
// TODO convert singleton with member ref variables
// TODO implement GLFW event callbacks

#include <iostream>
#include <chrono>

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

#include <glm/glm.hpp>

#include <Vega/Core/Core.hpp>
#include <Vega/Core/Application.hpp>

int main(int argc, char **argv) {
  auto app = Vega::Make();

  app->Run();

  delete app;
}