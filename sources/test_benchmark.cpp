#include "test_funcs.hpp"

#include "benchmark.h"

glm::vec3 temp_vecs[N];
const int result = pxd::fill_temp_array(temp_vecs);

static void BM_ReelFunc(benchmark::State &state) {
  size_t index = 0;

  for (auto _ : state) {
    pxd::reel_func(temp_vecs[index]);

    state.PauseTiming();
    ++index;
    state.ResumeTiming();
  }
}
BENCHMARK(BM_ReelFunc)->Name("Reel Cubemap Sampling")->Iterations(N);

static void BM_RefactoredFunc(benchmark::State &state) {
  size_t index = 0;

  for (auto _ : state) {
    pxd::refactored_func(temp_vecs[index]);

    state.PauseTiming();
    ++index;
    state.ResumeTiming();
  }
}
BENCHMARK(BM_RefactoredFunc)
    ->Name("Refactored Cubemap Sampling")
    ->Iterations(N);

BENCHMARK_MAIN();