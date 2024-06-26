#pragma once

#include "gles2.h"
#include "test_funcs.hpp"

namespace pxd {
GLuint get_vertex_array(GLuint buffer);

GLuint get_uniform_buffer(GLuint program);

GLuint get_shader_program(const char *vert_path, const char *frag_path);
GLuint get_compiled_shader(const char *path, GLenum shader_type);
void check_shader(GLuint shader);
} // namespace pxd