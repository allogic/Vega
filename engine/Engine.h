#ifndef VEGA_H
#define VEGA_H

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <functional>
#include <utility>

#include "FwDecls.h"
#include "Core.h"
#include "Singleton.h"
#include "Timestep.h"
#include "Layer.h"
#include "Event.h"
#include "Input.h"
#include "Application.h"
#include "EntryPoint.h"
#include "Shader.h"
#include "Camera.h"
#include "Vertex.h"
#include "Mesh.h"
#include "Transform.h"
#include "Model.h"

#endif