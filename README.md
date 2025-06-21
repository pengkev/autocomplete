# Autocomplete System in C

A simple, efficient, and fast autocomplete implementation in C using binary search and sorting techniques.

## Overview
This repository contains an implementation of an autocomplete feature that efficiently finds and ranks matching terms based on a given substring prefix. The terms are sorted lexicographically to facilitate quick binary searches, and the matching terms are then sorted by weight to provide meaningful autocomplete suggestions.

## Features
- Efficient binary search for fast term matching.
- Sorting suggestions by relevance (weight).
- Robust error handling and input validation.

## Structure
- **autocomplete.h** – Defines the `term` structure and function prototypes.
- **autocomplete.c** – Implementation of core functionalities:
  - `read_in_terms` – Reads and initializes the terms from a file.
  - `lowest_match` and `highest_match` – Binary search to find the matching substring range.
  - `autocomplete` – Generates sorted autocomplete suggestions.

## Installation & Usage

### Compile

Compile the program using GCC:

```bash
gcc -o autocomplete autocomplete.c main.c
````

Ensure you have `autocomplete.h`, `autocomplete.c`, and your entry-point file (e.g., `main.c`) ready.

### Input Data Format

Provide a file (`terms.txt`) with the following format:

* The first line indicates the number of terms.
* Subsequent lines contain each term’s weight, followed by a tab (`\t`), then the term itself.

Example:

```
4
5627187200\tToronto
3209457000\tTokyo
1234567000\tToronto Maple Leafs
987654321\tToledo
```

### Running the Program

Run the executable with:

```bash
./autocomplete terms.txt
```

Follow the on-screen instructions to provide the prefix string and get autocomplete suggestions.

## Example Output

```
Enter search prefix: To
Autocomplete suggestions:
1. Toronto (5627187200)
2. Tokyo (3209457000)
3. Toronto Maple Leafs (1234567000)
4. Toledo (987654321)
```

## Dependencies

* Standard C Library (`<stdio.h>`, `<stdlib.h>`, `<string.h>`)

## Error Handling

The program robustly handles:

* File I/O errors (missing file, incorrect format).
* Memory allocation failures.

## Contribution

Feel free to fork this repository, open issues, or submit pull requests for improvements or additional features.

## License

This project is open-source under the MIT license. Feel free to modify, distribute, and use as per the terms.

---

Developed with care and rigor in C to provide a fast and reliable autocomplete solution.

```

This README effectively communicates your project's purpose, structure, usage instructions, and expected inputs/outputs clearly and professionally.
```
