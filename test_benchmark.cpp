#include "test_funcs.hpp"

#include <random>

#include "benchmark.h"

std::random_device dev;
std::mt19937_64 random_engine(dev());
std::uniform_real_distribution<> generator(-1000000.f, 1000000.f);

static void BM_ReelFunc(benchmark::State &state) {

  for (auto _ : state) {
    state.PauseTiming();
    glm::vec3 temp_vec =
        glm::vec3(generator(random_engine), generator(random_engine),
                  generator(random_engine));
    state.ResumeTiming();
    pxd::reel_func(temp_vec);
  }
}
BENCHMARK(BM_ReelFunc)->Name("Reel Cubemap Sampling")->Iterations(N);

static void BM_RefactoredFunc(benchmark::State &state) {
  for (auto _ : state) {
    state.PauseTiming();
    glm::vec3 temp_vec =
        glm::vec3(generator(random_engine), generator(random_engine),
                  generator(random_engine));
    state.ResumeTiming();
    pxd::refactored_func(temp_vec);
  }
}
BENCHMARK(BM_RefactoredFunc)
    ->Name("Refactored Cubemap Sampling")
    ->Iterations(N);

BENCHMARK_MAIN();