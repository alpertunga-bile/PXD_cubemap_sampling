#include "core.h"
#include "os.h"

#include "test_funcs.hpp"

#include <random>

int main() {
  std::random_device dev;
  std::mt19937_64 random_engine(dev());
  std::uniform_real_distribution<> generator(-1000000.f, 1000000.f);

  int correct_counter = 0;

  auto log_file = fmt::output_file("errors.txt");

  for (int i = 0; i < N; i++) {
    glm::vec3 temp_vec =
        glm::vec3(generator(random_engine), generator(random_engine),
                  generator(random_engine));

    glm::vec3 temp_reel_res = pxd::reel_func(temp_vec);
    glm::vec3 temp_refactored_res = pxd::refactored_func(temp_vec);

    bool result = pxd::check_vec_equal(temp_reel_res, temp_refactored_res);

    if (result) {
      correct_counter += 1;
    } else {
      log_file.print(
          "Test : ({:7.2f}, {:7.2f}, {:7.2f}) | Reel : ({:.2f}, {:.2f}, "
          "{:.2f}) | Refactored : ({:.2f}, "
          "{:.2f}, {:.2f})\n",
          temp_vec.x, temp_vec.y, temp_vec.z, temp_reel_res.x, temp_reel_res.y,
          temp_reel_res.z, temp_refactored_res.x, temp_refactored_res.y,
          temp_refactored_res.z);
    }
  }

  fmt::print("Summary : {} / {}", correct_counter, N);

  return 0;
}