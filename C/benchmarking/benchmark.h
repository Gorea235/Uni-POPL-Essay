/*
 * Benchmark tool, for Win32/POSIX, fully C89 compliant.
 * Sourced from https://gist.github.com/RenatoUtsch/4162799
 * Modified by me (originally for another benchmarking project, tweaked for this one)
 */

#ifndef BENCHMARK_H_DEFINED
#define BENCHMARK_H_DEFINED
#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

/**
 * Benchmark what is done in the function passed on the first parameter.
 * @param func The callback function to call when the benchmark is started.
 * @param data The data to pass to the callback function.
 * @param numBytes The number of bytes of the data passed.
 * @param numBenchmarks The number of benchmarks to be done to return a more accurate result (recommended at least 100).
 * @return The time in seconds the function ran.
 **/
double benchmark(int func(int[], int), int items[], int len, int numBenchmarks);

#ifdef __cplusplus
}
#endif
#endif
