# student-grades

A C++ console program that reads students' homework and exam results, calculates their final grades, and compares how different containers perform on large data sets.

## Final points formula

Final points = 0.4 * (Average of HW | Median of HW) + 0.6 * Exam

- HW = homework results
- Exam = exam result
- Both the average-based and the median-based grade are calculated for every student.

## Project structure

| File | Purpose |
|---|---|
| `Person.h` / `Person.cpp` | `Person` class: name, surname, homework (`std::vector`), exam, final grades. Rule of three, overloaded `>>` and `<<`. |
| `FileGenerator.h` / `FileGenerator.cpp` | Generates random student files (1K, 10K, 100K, 1M, 10M records). |
| `GradeSplitter.h` / `GradeSplitter.cpp` | Reads a student file, calculates grades, splits students into passed (>= 5.0) and failed (< 5.0), writes two output files, and measures the time of each stage. Implemented for `std::vector`, `std::list` and `std::deque`. |
| `main.cpp` | Runs the generation and the three container tests, then prints the sorted table from `Students.txt`. |

## Exception handling

File operations are wrapped in `try / catch`. If a file cannot be opened or created, a `std::runtime_error` is thrown and `main` prints `Error: ...` instead of crashing.

## Build and run

```
g++ -o main main.cpp Person.cpp FileGenerator.cpp GradeSplitter.cpp
./main
```

On Windows PowerShell, run it with `.\main.exe`.

The 10 million record files are large (the input file is about 375 MB), so the full run takes several minutes. Generated files are excluded from Git through `.gitignore`.

## Output

For each container and file size the program prints the read, calculation, split and write times (in ms) and the number of passed and failed students.

## Releases

- **v0.1**: `Person` class, average/median grade, random scores, reading `Students.txt`.
- **v0.2**: refactoring into classes and files, exception handling, large file generation, pass/fail split, performance timing (`std::vector`).
- **v0.25**: same logic with `std::list` and `std::deque`, compared against `std::vector`.

## Sample results (total time, ms)

| Records | vector | list | deque |
|---|---|---|---|
| 10,000 | 109.8 | | 108.2 |
| 100,000 | 1103.9 | | 1111.2 |
| 1,000,000 | 10857.6 | 13373.5 | 10898.4 |
| 10,000,000 | 143373 | 129170 | |

Timings vary from run to run and depend on the machine.
