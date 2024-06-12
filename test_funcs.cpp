#include "test_funcs.hpp"

#ifndef GLM_FORCE_SWIZZLE
#define GLM_FORCE_SWIZZLE
#endif

#ifndef GLM_FORCE_INTRINSICS
#define GLM_FORCE_INTRINSICS
#endif

#include "glm.hpp"

namespace pxd {
glm::vec3 reel_func(const glm::vec3 &_vec) {
  glm::vec3 vec = _vec;

  float layer;
  glm::vec2 coord;
  glm::vec3 absVec = glm::abs(vec);

  if (absVec.x >= absVec.y && absVec.x >= absVec.z) {
    if (vec.x > 0.0) {
      layer = 0.0;
      vec /= vec.x;
      coord = -1.0f * vec.zy;
    } else {
      layer = 1.0;
      vec.y = -vec.y;
      vec /= vec.x;
      coord = -1.0f * vec.zy;
    }
  } else if (absVec.y >= absVec.x && absVec.y >= absVec.z) {
    if (vec.y > 0.0) {
      layer = 2.0;
      vec /= vec.y;
      coord = vec.xz;
    } else {
      layer = 3.0;
      vec.x = -vec.x;
      vec /= vec.y;
      coord = vec.xz;
    }
  } else {
    if (vec.z > 0.0) {
      layer = 4.0;
      vec.y = -vec.y;
      vec /= -vec.z;
      coord = -1.0f * vec.xy;
    } else {
      layer = 5.0;
      vec /= -vec.z;
      coord = -1.0f * vec.xy;
    }
  }

  coord = (coord + glm::vec2(1.0)) * 0.5f;
  return glm::vec3(coord, layer);
}

constexpr int arr_value_cache[3] = {-1, 0, 1};
constexpr int arr_index_cache[5] = {0, 1, 2, 0, 1};

glm::vec3 refactored_func(const glm::vec3 &_vec) {
  glm::vec3 vec = _vec;
  glm::vec3 absVec = glm::abs(vec);

  int index = ((absVec.y > absVec.z) && (absVec.y > absVec.x)) +
              (((absVec.z > absVec.y) && (absVec.z > absVec.x)) * 2);

  int max_value_sign = arr_value_cache[(int)glm::sign(vec[index]) + 1];

  float layer = (float)index * 2.0f;

  if (max_value_sign == -1) {
    layer += 1.0f;
  }

  if (index == 2) {
    vec.y *= -1.0f;
    vec.z *= -1.0f;
  }

  vec[(index + 1) % 2] *= (float)max_value_sign;

  vec /= vec[index];

  glm::vec2 coord =
      glm::vec2(vec[(index + 2) % 3], vec[(index + 1) % 3]) * -1.0f;

  switch (index) {
  case 1:
    coord *= -1.0f;
    break;
  case 2:
    coord = coord.yx;
    break;
  }

  coord = (coord + glm::vec2(1.0)) * 0.5f;
  return glm::vec3(coord, layer);
}

constexpr float EPSILON = 0.00001f;

bool check_vec_equal(const glm::vec3 &a, const glm::vec3 &b) {
  for (int i = 0; i < 3; i++) {
    if (std::abs(a[i] - b[i]) > EPSILON) {
      return false;
    }
  }

  return true;
}
} // namespace pxd