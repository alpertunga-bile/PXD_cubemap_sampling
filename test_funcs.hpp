#pragma once

#ifndef GLM_FORCE_SWIZZLE
#define GLM_FORCE_SWIZZLE
#endif

#ifndef GLM_FORCE_INTRINSICS
#define GLM_FORCE_INTRINSICS
#endif

constexpr int N = 1000000;

#include "vec3.hpp"

namespace pxd {
glm::vec3 reel_func(glm::vec3 vec);
glm::vec3 refactored_func(glm::vec3 vec);

bool check_vec_equal(const glm::vec3 &a, const glm::vec3 &b);
} // namespace pxd