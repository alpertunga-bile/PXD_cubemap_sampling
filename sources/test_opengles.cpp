#include "gles_funcs.hpp"

#define GLFW_INCLUDE_NONE
#include "glfw3.h"

#include "core.h"

constexpr int WIN_WIDTH = 1280;
constexpr int WIN_HEIGHT = 720;
constexpr size_t NUM_ITER = 99'999'999;

int main() {
  int result = glfwInit();

  if (result != GLFW_TRUE) {
    fmt::print("Can't initialize GLFW");
    return 1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window = glfwCreateWindow(
      WIN_WIDTH, WIN_HEIGHT, "Cubemap OpenGL ES Test", nullptr, nullptr);

  if (window == NULL) {
    fmt::print("Can't create GLFW window");
    return 1;
  }

  glfwMakeContextCurrent(window);
  result = gladLoadGLES2(glfwGetProcAddress);

  GLuint program = pxd::get_shader_program();

  while (!glfwWindowShouldClose(window)) {

    glfwPollEvents();
    glfwSwapBuffers(window);
  }

  glfwDestroyWindow(window);

  return 0;
}