#! /usr/bin/env python2
import timeit
import sys
import threading

# allow for deep recursion
sys.setrecursionlimit(1000000)

DEFAULT_REPEAT_AMOUNT = 100  # the number of times to repeat the meaturements
DEFAULT_TIME_AMOUNT = 1  # the number of times to measure the function


def gen_list(n):
    # generates a list of n long
    return [i for i in range(n)]


class Span:
    """Provides access over a list via reference rather than re-allocation.
    This object will act like a standard list that has been spliced (meaning functions
    like 'len' will work correctly), however it will not cause any re-allocations beyond
    the Span object itself (the list doesn't actually change, just the referencing of
    it does).

    Inspired by C#'s Span<T>, written by Luke. This is the original, simple, implementation
    I wrote for this project. A complete implementation (written by me separately) is up
    at https://github.com/Gorea235/Spanning.

    Params:
        over: the list-like object to span over (can be another Span object).
        start: the starting point of the span (if None, defaults to 0) (inclusive).
        end: the ending point of the span (if None, defaults to the end of over) (exclusive).
    """

    def __init__(self, over, start=None, end=None):
        offset = 0
        self.__over = over
        if isinstance(over, Span):
            self.__over = over.__over
            offset = over.__slice.start
        over_ln = len(self.__over)
        start = (0 if start is None else start) + offset
        end = over_ln - offset if end is None else end + offset
        self.__slice = slice(start, end)
        self.__indices = self.__slice.indices(over_ln)

    def __key_to_actual(self, key):
        if key < 0 or key >= len(self):
            raise IndexError("span index out of range")
        return self.__indices[0] + key

    def __getitem__(self, key):
        return self.__over[self.__key_to_actual(key)]

    def __len__(self):
        ln = self.__indices[1] - self.__indices[0]
        if ln < 0:
            return 0
        return ln

    def __repr__(self):
        sb = "["
        ln = len(self)
        for i in range(ln):
            sb += str(self[i])
            if i < ln - 1:
                sb += ", "
        return sb + "]"

    def __str__(self):
        return repr(self)


def do_sum_im(lst):
    # main implementation using Span class
    if len(lst) > 0:
        return lst[0] + do_sum_im(Span(lst, 1))
    else:
        return 0


def do_sum_im_slice(lst):
    # secondary implementation using list slicing
    # only included to show benchmarks (not included in graphs)
    if len(lst) > 0:
        return lst[0] + do_sum_im_slice(lst[1:])
    else:
        return 0


def do_sum_m(lst):
    # mutable looping implementation
    total = 0
    for i in lst:
        total += i
    return i


def bench_main_internal(f, n):
    # the internal benchmarking function
    # takes in the function name and the length of the list
    # outputs the minimum run time
    bnc = min(timeit.repeat("{}(lst)".format(f),
                            "from __main__ import {}, gen_list ; lst = gen_list({})".format(
        f, n),
        repeat=DEFAULT_REPEAT_AMOUNT,
        number=DEFAULT_TIME_AMOUNT)) / DEFAULT_TIME_AMOUNT
    print("> {} runs with the minimum time of {} seconds (which is the average over {} repeats)".format(
        DEFAULT_REPEAT_AMOUNT, bnc, DEFAULT_TIME_AMOUNT))


def bench_main(n, im, slc):
    # performs all the benchmarks using the given list length
    # takes in parameters for whether the run the immutable with span and
    # immutable with slice functions, as they stop working with high list
    # lengths
    print("====== benchmarking with list of {} items ======".format(n))
    if im:
        print("---===--- benchmarking immutable w/ span ---===---")
        bench_main_internal("do_sum_im", n)
    if slc:
        print("---===--- benchmarking immutable w/ slice ---===---")
        bench_main_internal("do_sum_im_slice", n)
    print("---===--- benchmarking mutable ---===---")
    bench_main_internal("do_sum_m", n)
    print("")


def bench():
    # entry point for benchmarks
    bench_main(10000, True, True)  # 10,000 items
    bench_main(100000, True, False)  # 100,000 items
    bench_main(1000000, False, False)  # 1,000,000 items


if __name__ == "__main__":
    # due to python stack size and frame limitations, we have to increase
    # the stack size to allow deeper recursion, and then run the benchmarks
    # in a thread with this new configuration
    threading.stack_size(2**27)  # 16 MB
    t = threading.Thread(target=bench)
    t.start()
