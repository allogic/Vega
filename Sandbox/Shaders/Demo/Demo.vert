layout (location = 0) in vec3 l_position;
layout (location = 1) in vec3 l_normal;

out vec3 position;
out vec3 normal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main() {
  position = vec3(model * vec4(l_position, 1.0));
  normal = mat3(model) * l_normal;

  gl_Position = projection * view * vec4(position, 1.0);
}
