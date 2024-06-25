#pragma once

#ifndef GLM_FORCE_SWIZZLE
#define GLM_FORCE_SWIZZLE
#endif

#ifndef GLM_FORCE_INTRINSICS
#define GLM_FORCE_INTRINSICS
#endif

constexpr size_t N = 10'000'000;

#include "vec3.hpp"

namespace pxd {
glm::vec3 reel_func(glm::vec3 vec);
glm::vec3 refactored_func(glm::vec3 vec);

bool check_vec_equal(const glm::vec3 &a, const glm::vec3 &b);
int fill_temp_array(glm::vec3 arr[]);
int fill_temp_array(float *arr, size_t size);
} // namespace pxd
