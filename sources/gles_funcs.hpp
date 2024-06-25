#pragma once

#include "gles2.h"

namespace pxd {
GLuint get_shader_program();

GLuint get_compiled_shader(const char *path, GLenum shader_type);

void check_shader(GLuint shader);
} // namespace pxd