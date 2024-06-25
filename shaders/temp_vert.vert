#version 310 es

layout(location = 0) in vec3 random_dirs;

layout(location = 0) out vec3 random_dir;
layout(location = 1) out vec3 color;

void main() {
  vec2 positions[3] = vec2[](vec2(0.0, -0.5), vec2(0.5, 0.5), vec2(-0.5, 0.5));
  vec3 colors[3] =
      vec3[](vec3(1.0, 0.0, 0.0), vec3(0.0, 1.0, 0.0), vec3(0.0, 0.0, 1.0));

  random_dir = random_dirs;
  color = colors[gl_VertexID % 3];

  gl_Position = vec4(positions[gl_VertexID % 3], 0.0, 1.0);
}