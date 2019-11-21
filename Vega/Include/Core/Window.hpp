#ifndef WINDOW_HPP
#define WINDOW_HPP

#pragma once

#include <Std.hpp>

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <imgui.h>
#include <examples/imgui_impl_glfw.h>
#include <examples/imgui_impl_opengl3.h>

#include <Core/Core.hpp>

#include <Utility/Settings.hpp>

namespace Vega::Core::Window {
  static GLFWwindow *Init() {
    auto &settings = Vega::Utility::Settings::Instance();

    if (!glfwInit()) {
      VEGA_ERROR("Failed to initialize glfw")
      return nullptr;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, settings.Get<int>("gl-major"));
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, settings.Get<int>("gl-minor"));
    glfwWindowHint(GLFW_SAMPLES, settings.Get<int>("antialiasing"));
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    int width = settings.Get<int>("width");
    int height = settings.Get<int>("height");
    std::string title = settings.Get<std::string>("title");

    GLFWwindow *window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    if (!window) {
      VEGA_ERROR("Failed to create window")
      return nullptr;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGL()) {
      VEGA_ERROR("Failed to initialize glad")
      return nullptr;
    }

    return window;
  }

  static void Destroy(GLFWwindow *window) {
    glfwDestroyWindow(window);
    glfwTerminate();
  }
}

#endif