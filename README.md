# WordGenerator

A small C library and command-line tool that enumerates every string of a
given length over a fixed alphabet, in lexicographic order.

For an alphabet of `n` characters and a target length `k`, the program emits
all `n^k` words by treating the output as a `k`-digit number in base `n`
and incrementing it from right to left with carry — the same mechanism a
mechanical odometer uses.

## Why it's interesting

- **Clean separation** between algorithm and I/O: the library accepts a
  callback per word, so the same engine drives the CLI, the test suite, or
  any other sink.
- **Iterative carry-propagation counter** in place of the recursive
  prototype it grew out of — bounded stack, simpler control flow.
- **Hermetic GoogleTest suite** wired in via CMake `FetchContent`: no
  system-installed dependencies required.
- **Doxygen-documented** public API, compiled with `-Wall -Wextra
  -Wpedantic` warning-clean on GCC 11+.

## Build and run

```bash
cmake -S . -B build
cmake --build build -j
./build/word_generator artur 3      # 125 words, one per line
```

Run the test suite:

```bash
ctest --test-dir build --output-on-failure
```

Generate API docs (requires `doxygen`):

```bash
doxygen docs/Doxyfile
xdg-open docs/build/html/index.html
```

## Project layout

```
WordGenerator/
├── CMakeLists.txt              # Build configuration
├── include/word_generator.h    # Public API + Doxygen
├── src/word_generator.c        # Library: counter + callback loop
├── src/main.c                  # CLI front-end
├── tests/test_word_generator.cpp   # GoogleTest suite (11 cases)
└── docs/Doxyfile               # API docs configuration
```

## Library API

```c
#include "word_generator.h"

bool print(const char *word, void *user_data) {
    (void)user_data;
    puts(word);
    return true;   /* return false to stop early */
}

generate_words("01", 2, 4, print, NULL);   /* 16 binary strings of length 4 */
```

Duplicate characters in the alphabet are allowed and produce duplicate
output words — the generator iterates over index combinations, not
distinct values.

## License

Provided as-is for educational and portfolio purposes.
