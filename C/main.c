#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "benchmarking/benchmark.h"

#ifndef NUM_BENCHES
#define NUM_BENCHES 10000
#endif

void fill_list(int items[], int len)
{
    for (int i = 0; i < len; i++)
        items[i] = i + 1;
}

int mutable_sum(int items[], int len)
{
    int total = 0;
    // int i;
    for (int i = 0; i < len; i++)
        total += items[i];
    return total;
}

int _immutable_sum_internal(int items[], int start, int end)
{
    if (start < end)
        return items[start] + _immutable_sum_internal(items, start + 1, end);
    else
        return 0;
}

int immutable_sum(int items[], int len)
{
    return _immutable_sum_internal(items, 0, len);
}

void do_benches(int len)
{
    int sampleList[len];
    double bench;

    fill_list(sampleList, len);
    bench = benchmark(mutable_sum, sampleList, len, NUM_BENCHES);
    printf("(mutable)   - %d benchmarks with %'d length list: min %.17gs\n", NUM_BENCHES, len, bench);
    bench = benchmark(immutable_sum, sampleList, len, NUM_BENCHES);
    printf("(immutable) - %d benchmarks with %'d length list: min %.17gs\n", NUM_BENCHES, len, bench);
}

int main(int argc, char *argv[])
{
    do_benches(10000);   // 10,000 items
    do_benches(100000);  // 100,000 items
    do_benches(1000000); // 1,000,000 items

    // the following are the maximum length of lists I was able to
    // create. the first was the maximum before adding the <locale.h> reference,
    // the second was the maximum after. I do not know how these would change when
    // this is run on another computer, so I have commented both out for safety.
    // do_benches(2096184); // max items
    // do_benches(2096128); // max items
    return 0;
}
