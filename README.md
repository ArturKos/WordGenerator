# WordGenerator

A **word and combination generator** built with **C++ Builder 6** that produces all possible strings of a given length from a character alphabet using recursive permutation.

![C++](https://img.shields.io/badge/C%2B%2B-Builder%206-blue)
![Windows](https://img.shields.io/badge/Platform-Windows-0078D6)
![Algorithm](https://img.shields.io/badge/Algorithm-Combinatorics-green)

## Features

- **Exhaustive word generation** -- produces every possible combination of characters for a specified word length
- **Recursive index advancement** -- uses a recursive `NastepneSlowo` (NextWord) function that increments character indices with carry propagation, similar to an odometer
- **Configurable alphabet** -- define any set of characters as the generation dictionary
- **VCL GUI** -- displays all generated words in a scrollable `TMemo` component
- **Termination detection** -- `Koniec_Budowy` (EndOfBuild) checks when all indices have reached their maximum value

## How It Works

The algorithm treats each position in the word as a digit in a variable-base number system:

1. An integer array (`slowo`) tracks the current character index at each position
2. `NastepneSlowo` increments the rightmost index; on overflow, it resets to 0 and recurses left (carry)
3. `ZapiszSlowo` maps the index array to characters from the alphabet and appends the result
4. Generation continues until all positions hold the maximum index value

For an alphabet of length `n` and word length `k`, the generator produces `n^k` combinations.

**Example:** Alphabet `"artur"` (5 chars), length 5 = 3,125 combinations.

## Dependencies

| Component | Purpose |
|-----------|---------|
| C++ Builder 6 | IDE, VCL framework, and compiler |

## Building

1. Open `Slownik.bpr` in **C++ Builder 6**.
2. Press **F9** to build and run.

## Usage

1. Launch the application.
2. Click the button to generate all word combinations.
3. Results appear in the memo field, one word per line.

The alphabet and word length are currently defined in source code (`BudujSlowa` call in `Button1Click`). Modify the character array and length parameter to customize generation.

## Project Structure

```
WordGenerator/
├── Slownik.cpp       # Application entry point (WinMain)
├── Slownik.bpr       # C++ Builder 6 project file
├── Slownik.res       # Compiled resource file
├── main.cpp          # Word generation logic and form event handlers
├── main.h            # TForm1 class declaration (Button, Memo)
├── main.dfm          # Form layout definition
└── main.ddp          # Diagram file
```

## License

This project is provided as-is for educational purposes.
