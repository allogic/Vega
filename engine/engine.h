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
#include <vector>

#include "fwdecls.h"
#include "singleton.h"
#include "timestep.h"
#include "application.h"
#include "entrypoint.h"
#include "shader.h"
#include "camera.h"
#include "vertex.h"
#include "mesh.h"
#include "transform.h"
#include "model.h"

#endif