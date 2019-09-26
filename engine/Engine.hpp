#ifndef VEGA_ENGINE_HPP
#define VEGA_ENGINE_HPP

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <functional>
#include <utility>

#include "FwDecls.hpp"

#include "Core.hpp"
#include "Layer.hpp"
#include "Event.hpp"
#include "Application.hpp"
#include "Input.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "Vertex.hpp"
#include "Mesh.hpp"
#include "Transform.hpp"
#include "Model.hpp"

#include "EntryPoint.hpp"

#endif