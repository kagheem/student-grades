# student-grades

A C++ console program that reads students' homework and exam results, calculates their final points, splits the students into **passed** and **failed**, and measures how the container type (`std::vector`, `std::list`, `std::deque`) and the splitting strategy affect the speed.

## Final points formula

Final points = 0.4 * (Average of HW | Median of HW) + 0.6 * Exam

Both the average-based and the median-based result are calculated. A student **passed** with final points >= 5.0 (average-based) and **failed** with final points < 5.0.

## Releases

| Release | Branch | What it contains |
|---|---|---|
| v0.1 | `v0.1` | `Person` class (rule of three, overloaded `>>` and `<<`), average/median grade, `std::vector` for homework, random scores, reading `Students.txt`, sorted table output. |
| v0.2 | `v0.2` | Code split into classes and `.h`/`.cpp` files, exception handling, random file generator (10K to 10M records), pass/fail split into two files, timing of every stage (`std::vector`). |
| v0.25 | `v0.25` | The same logic with `std::list` and `std::deque`, compared with `std::vector` on 5 file sizes. |
| v1.0 | `v1.0` / `main` | Menu, two splitting strategies on all three containers, a faster Strategy 3 using `<algorithm>`, Makefile and CMakeLists.txt, clean repository. |

## Project structure

| File | Purpose |
|---|---|
| `Person.h`, `Person.cpp` | `Person` class: name, surname, homework (`std::vector<double>`), exam, final points. |
| `FileGenerator.h`, `FileGenerator.cpp` | Generates a file with random students (placeholder names, random scores). |
| `GradeSplitter.h` | Template class. `GradeSplitter::run<Container>(...)` reads a file, calculates the grades, splits the students, writes the two result files and prints the time of every stage. Template code lives in the header. |
| `main.cpp` | Menu: file size, container, strategy. |
| `Students.txt` | Small sample input file. |
| `Makefile`, `CMakeLists.txt` | Build files for Unix (make) and for any OS (CMake). |

## Splitting strategies

- **Strategy 1:** copy the students into **two new** containers, `passed` and `failed`. The original container keeps everyone. It uses more memory, but it is fast.
- **Strategy 2 (manual loop):** create **one new** container (`failed`). Walk through the original container, copy each failed student into the new container and `erase` it from the original. Only passed students remain in the original, and the container is then shrunk. Every `erase` in the middle of a `vector` or `deque` shifts all the following elements, so this is very slow.
- **Strategy 3 (algorithms):** the same result as Strategy 2, written with `<algorithm>`: `std::copy_if` copies the failed students, and `std::remove_if` plus a single `erase` removes them in one pass (the erase-remove idiom). Strategy 1 also uses `std::copy_if`, and the grade calculation uses `std::for_each`.

## Usage guide

### 1. Build with Make (Linux / macOS / MSYS2)

```
make
./main
```

`make clean` removes the build files.

### 2. Build with CMake (any OS)

```
cmake -S . -B build
cmake --build build
```

The program is `build/main` (on Windows with some generators it is in `build/Release/main.exe`). Run it from the folder where you want the data files to appear.

### 3. Build without Make or CMake

```
g++ -std=c++17 -O2 -o main main.cpp Person.cpp FileGenerator.cpp
```

On Windows PowerShell run it with `.\main.exe`.

### 4. Use the menu

1. Choose the **file size**: 1000, 10000, 100000, 1000000 or 10000000. If the file does not exist, it is generated automatically (`students_<N>.txt`).
2. Choose the **container**: vector, list, deque, or all three.
3. Choose the **strategy**: 1, 2, 3 or all.
4. The program prints read, calculation, split, write and total time, and the number of passed and failed students. The results are written to `passed_s<strategy>_<container>_students_<N>.txt` and `failed_s<strategy>_<container>_students_<N>.txt`.
5. Enter `0` to exit.

**Warning:** do not run Strategy 2 (or "all") on `vector` or `deque` with 100,000 or more records. It takes very long, because the time grows quadratically. Generated files are large (the 10M file is about 375 MB), and they are excluded from Git by `.gitignore`.

## Results

Machine: Windows, MSYS2 g++ 16.2, compiled with `-O2`. Times are in milliseconds from single runs, except where noted, and they vary from run to run.

### Split time (the part that depends on the strategy)

| Records | Container | Strategy 1 | Strategy 2 | Strategy 3 |
|---|---|---|---|---|
| 10,000 | vector | 2.3 | 318.0 | 2.1 |
| 10,000 | list | 1.8 | 0.6 | 1.8 |
| 10,000 | deque | 1.8 | 97.3 | 1.1 |
| 100,000 | vector | 30.3 | not run | 22.2 |
| 100,000 | list | 26.8 | not run | 20.7 |
| 100,000 | deque | 30.6 | not run | 26.8 |
| 1,000,000 | vector | 163.2 | not run | 153.4 to 159.9 |
| 1,000,000 | list | 174.9 | not run | 142.9 to 144.5 |
| 1,000,000 | deque | 125.8 | not run | **98.6 to 100.3** |

The Strategy 3 values at 1,000,000 are three runs (range shown).

### Total time at 1,000,000 records

| Container | Strategy 1 | Strategy 3 |
|---|---|---|
| vector | 13505 | 11017 to 11443 |
| list | 10732 | 10123 to 10340 |
| deque | 10658 | **9939 to 10367** |

### Comments on the results

- **Strategy 2 is the slowest on `vector` and `deque`.** At 10,000 records it was about 150 times slower than Strategy 3 on `vector` and about 90 times slower on `deque`. Each `erase` shifts every following element, and each shift copies a whole `Person`. `list` does not have this problem, because removing a node does not move other elements (0.6 ms).
- **I did not run Strategy 2 on large files.** Its cost grows quadratically, so I estimate (not measured) about 30 seconds at 100,000 and close to an hour at 1,000,000 on `vector`.
- **Strategy 3 is the fastest or tied in every measured case.** It does the same work as Strategy 2, but `std::remove_if` moves each element at most once. It also needs less memory than Strategy 1, because only the failed students are copied.
- **The fastest combination is `std::deque` with Strategy 3.** At 1,000,000 records it was the fastest in all three runs (about 99 ms, against about 143 ms for `list` and about 157 ms for `vector`). At 100,000 records `list` was slightly faster than `deque` in a single run, so the difference between the containers is small at that size.
- **Splitting is a small part of the total time.** Reading the file takes about 90% of the total time at 1,000,000 records, so the total times of the three containers are close, and the read time itself varies by about 10% between runs.
- **Earlier releases are not directly comparable.** v0.2 and v0.25 were compiled without `-O2` and wrote output with `std::endl`. Their totals at 1,000,000 records were about 10.9 s (vector), 13.4 s (list) and 10.9 s (deque) for the whole process.

## Exception handling

Opening or creating a file that fails throws `std::runtime_error`. The menu catches it, prints `Error: ...` and keeps running instead of crashing.