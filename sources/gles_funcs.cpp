#include "gles_funcs.hpp"

#ifndef GLAD_GLES2_IMPLEMENTATION
#define GLAD_GLES2_IMPLEMENTATION
#endif

#include "gles2.h"

#include "temp_vert_spv.h"

#include <string>

GLuint pxd::get_shader_program() {
  GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);

  glShaderBinary(1, &vertex_shader, GL_UNSIGNED_INT, temp_vert_spv,
                 sizeof(temp_vert_spv) / sizeof(uint32_t));

  GLuint program = 0;

  return program;
}