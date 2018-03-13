# Uni Y2 POPL Benchmarking Project
This repository contains the project used to benchmark the various functions used for the essay for my year 2 POPL module. It has the Prolog ([prolog-bench.pl](prolog-bench.pl)), Scheme ([scheme-bench.rkt](scheme-bench.rkt)), and Python ([python-bench.py](python-bench.py)) benchmarking files. It also has optional C ([C/](C)) benchmarks, which were written to see the fastest possible execution time of the function (as C is a fast, low-level language). The C benchmarking was sourced from my [previous benchmarking repo](https://github.com/Gorea235/benchmarking).

The function we had to implement was one that summed up all the elements in a list of integers. We had to implement mutable and immutable versions of this in each language.

## Running
The shell file [bench](bench) is the main file used to execute the benchmarks. It is set up for my environment (macOS with python2 and swipl in PATH, and DrRacket installed, but not on PATH), so it may require some slight tweaks to some of the executables to get it working. When run, it will automatically run all of the benchmarks in this project (including C, however this can be commented out if not wanted). It will also attempt some formatting to make the output more readable.

The bench script currently assumes the following:

- `swipl` is installed and in PATH
- `racket` is installed in the directory `/Applications/Racket v6.12/bin/racket`
  - This is specific to macOS, but the path is specified by the variable `RACKET_PATH` at the top of the file (change it to the actual path, or just the executable if `racket` is in PATH)
- `python2` is installed and in PATH
  - Depending on OS, this could change
  - For example, `python` on macOS, defaults to Python 2, however most installations support the more specific `python2` command
- `make` and `gcc` are installed and in PATH
  - These are only needed for the C benchmarks, they can be removed if you don't want them or one/both of these are not installed
