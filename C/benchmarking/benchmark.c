/*
 * Implementation of the benchmark tool.
 * Sourced from https://gist.github.com/RenatoUtsch/4162799
 * Modified by me (originally for another benchmarking project, tweaked for this one)
 */

#include "benchmark.h"

#ifndef __cplusplus
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#else
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;
#endif

/**
 * Gets the current time.
 * @return The current time, in seconds.
 **/
double get_current_time();

double benchmark(int func(int[], int), int lst[], int len, int numBenchmarks)
{
    double min_time = -1;

    // printf("----------------------------\nStarting benchmark...\n----------------------------\n");

    for (int i = 0; i < numBenchmarks; ++i)
    {
        double start_time = 0.0; /** The time the benchmark started. **/
        double end_time = 0.0;   /** The time the benchmark ended. **/
        double bench_time = 0.0; /** end_time - start_time **/

        /* Start the benchmark. */
        start_time = get_current_time();

        /* Call the function to benchmark. */
        func(lst, len);

        /* End the benchmark. */
        end_time = get_current_time();
        bench_time = end_time - start_time;

        // set the minimum time
        // if min_time < 0, then it hasn't been set yet
        if (min_time < 0)
            min_time = bench_time;
        else if (bench_time < min_time)
            min_time = bench_time;
    }

    // Return the minimum time.
    return min_time;
}

/* Implement get_current_time() depending on the OS. */
#if defined(WIN32) || defined(__WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN32_)

#include <windows.h>

double get_current_time()
{
    LARGE_INTENGER t, f;
    QueryPerformanceCounter(&t);
    QueryPerformanceFrequency(&f);
    return (double)t.QuadPart / (double)f.QuadPart;
}

#else

#include <sys/time.h>
#include <sys/resource.h>

double get_current_time()
{
    struct timeval t;
    gettimeofday(&t, 0);
    return t.tv_sec + t.tv_usec * 1e-6;
}

#endif
