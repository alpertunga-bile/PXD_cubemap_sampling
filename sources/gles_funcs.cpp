#include "gles_funcs.hpp"

#include <filesystem>
#include <fstream>
#include <sstream>

#ifndef GLAD_GLES2_IMPLEMENTATION
#define GLAD_GLES2_IMPLEMENTATION
#endif

#include "gles2.h"

#include "core.h"

namespace pxd {
GLuint get_shader_program() {
  fmt::println("Vertex Shader");
  GLuint vertex_shader =
      get_compiled_shader("shaders/temp.vert", GL_VERTEX_SHADER);
  fmt::println("Fragment Shader");
  GLuint frag_shader =
      get_compiled_shader("shaders/temp.frag", GL_FRAGMENT_SHADER);

  GLuint program = glCreateProgram();

  glAttachShader(program, vertex_shader);
  glAttachShader(program, frag_shader);

  glLinkProgram(program);

  glDetachShader(program, vertex_shader);
  glDetachShader(program, frag_shader);

  glDeleteShader(vertex_shader);
  glDeleteShader(frag_shader);

  return program;
}

GLuint get_compiled_shader(const char *path, GLenum shader_type) {
  if (std::filesystem::exists(path) == false) {
    fmt::println("{} is not exists", path);
    return 0;
  }

  std::ifstream reader;
  std::string shader_source;
  reader.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  try {
    reader.open(path);

    std::stringstream stream;
    stream << reader.rdbuf();
    shader_source = stream.str();
    reader.close();
  } catch (std::ifstream::failure e) {
    if (reader.is_open()) {
      reader.close();
    }
  }

  GLuint shader = glCreateShader(shader_type);

  const GLchar *code_arr[] = {shader_source.c_str()};

  glShaderSource(shader, 1, code_arr, NULL);

  glCompileShader(shader);

  check_shader(shader);

  return shader;
}

void check_shader(GLuint shader) {
  int success;
  char info_log[512];
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

  if (success) {
    return;
  }

  glGetShaderInfoLog(shader, 512, NULL, info_log);
  fmt::println("::Shader Error:: {}", info_log);
}

} // namespace pxd