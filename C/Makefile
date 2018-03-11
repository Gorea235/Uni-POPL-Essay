INPUT=main.c benchmarking/benchmark.c
OUTPUT_DIR=bin/
OUTPUT=benchmark

build:
	mkdir -p $(OUTPUT_DIR)
	gcc -O2 $(INPUT) -o $(OUTPUT_DIR)$(OUTPUT)

clean:
	rm -f *.o

.PHONY: clean build