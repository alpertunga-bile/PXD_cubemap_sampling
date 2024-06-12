#include "test_funcs.hpp"

#ifndef GLM_FORCE_SWIZZLE
#define GLM_FORCE_SWIZZLE
#endif

#ifndef GLM_FORCE_INTRINSICS
#define GLM_FORCE_INTRINSICS
#endif

#include "glm.hpp"

namespace pxd {
glm::vec3 reel_func(glm::vec3 vec) {

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

constexpr float EPSILON = 0.00001f;

inline int sign(float x) noexcept {
  if (x < 0.f) {
    return -1;
  } else {
    return 1;
  }

  return 1;
}

inline int get_max_index(glm::vec3 &&vec) noexcept {
  int results[3] = {0, 0, 0};
  int i = 0;

  results[0] = (vec.x >= vec.y) && (vec.x >= vec.z);
  results[1] = ((vec.y >= vec.z) && (vec.y >= vec.x));
  results[2] = ((vec.z >= vec.y) && (vec.z >= vec.x));

  for (; i < 3; i++) {
    if (results[i] == i) {
      return i;
    }
  }

  return 0;
}

glm::vec3 refactored_func(glm::vec3 vec) {

  int index = get_max_index(glm::abs(vec));

  int max_value_sign = sign(vec[index]);

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

  glm::vec2 coord(vec[(index + 2) % 3], vec[(index + 1) % 3]);

  switch (index) {
  case 0:
    coord *= -1.0f;
    break;
  case 2:
    coord = coord.yx * -1.0f;
    break;
  }

  coord = (coord + glm::vec2(1.0)) * 0.5f;
  return glm::vec3(coord, layer);
}

bool check_vec_equal(const glm::vec3 &a, const glm::vec3 &b) {
  for (int i = 0; i < 3; i++) {
    if (std::abs(a[i] - b[i]) > EPSILON) {
      return false;
    }
  }

  return true;
}
} // namespace pxd