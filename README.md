# get_next_line

A C implementation of `get_next_line(int fd)` that reads from a file descriptor and returns one line per call with predictable memory behavior.

**Score: 125/100**

## Overview

`get_next_line` was built as part of the 42 curriculum to practice low-level stream processing and memory management in C.
The project solves incremental line reading without loading entire files into memory, which is a common requirement in systems programming and parser-style workflows.

The implementation focuses on:
- Correct line boundaries across partial reads
- Stateful reading using static storage
- Reliable behavior on EOF, invalid descriptors, and read/allocation failures

## Demo / Screenshots

This is a library-level C project, so there is no graphical UI.

## Tech Stack

- Language: C
- APIs: POSIX `read`
- Build tooling: `cc` (GCC/Clang), standard compiler flags
- Dependencies: none (custom utility functions included)

## Architecture / Implementation

### Core Flow

1. Read chunks of size `BUFFER_SIZE` from a file descriptor.
2. Append chunks to persistent storage until a newline or EOF is reached.
3. Extract the next line to return.
4. Keep the remainder for the next function call.

### Main Modules

- `get_next_line.c`: mandatory single-FD implementation
- `get_next_line_utils.c`: string and memory helper utilities
- `get_next_line.h`: mandatory prototypes and configuration
- `get_next_line_bonus.c`: multi-FD bonus implementation
- `get_next_line_utils_bonus.c`: bonus helper utilities
- `get_next_line_bonus.h`: bonus prototypes and configuration

### Key Technical Decisions

- Used static storage to preserve unread data between calls.
- Made `BUFFER_SIZE` compile-time configurable for testing different read granularities.
- Kept utility functions local to the project to avoid external library dependencies.
- Implemented bonus support with per-file-descriptor static storage for interleaved reads.

## Features

- Returns one line per call, including trailing `\n` when present
- Works with regular files, stdin, and other readable file descriptors
- Handles EOF and error cases by returning `NULL`
- Supports configurable chunk size via `BUFFER_SIZE`
- Includes bonus behavior for reading from multiple FDs in parallel

## Getting Started

### Prerequisites

- GCC or Clang
- Linux or macOS shell environment

### 1) Clone the Repository

```bash
git clone https://github.com/chilituna/get_next_line.git
cd get_next_line
```

### 2) Integration Overview

To use `get_next_line` in your project, you have two approaches:

#### Option A: Compile with Your Project

Copy or link the source files into your project and compile them together:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 your_program.c get_next_line.c get_next_line_utils.c
```

#### Option B: Compile into an Object File First

Compile the library separately, then link it:

```bash
cc -c -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
cc -Wall -Wextra -Werror your_program.c get_next_line.o get_next_line_utils.o -o program
```

### 3) Example: Reading a File Line by Line

Include the header and use the function:

```c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

int main(void)
{
	int		fd;
	char	*line;

	fd = open("example.txt", O_RDONLY);
	if (fd < 0)
		return (1);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);  // Line already includes the newline
		free(line);          // Always free the returned line
	}
	close(fd);
	return (0);
}
```

### 4) Using the Bonus Version (Multiple File Descriptors)

The bonus version allows reading from multiple files simultaneously:

```c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line_bonus.h"

int main(void)
{
	int		fd1 = open("file1.txt", O_RDONLY);
	int		fd2 = open("file2.txt", O_RDONLY);
	char	*line;

	// Interleaved reads from different files
	line = get_next_line(fd1);  // First line from file1
	printf("File1: %s", line);
	free(line);

	line = get_next_line(fd2);  // First line from file2
	printf("File2: %s", line);
	free(line);

	line = get_next_line(fd1);  // Second line from file1 (state preserved)
	printf("File1: %s", line);
	free(line);

	close(fd1);
	close(fd2);
	return (0);
}
```

### 5) Important Notes

- **Memory Management**: Always `free()` the returned line when done with it.
- **BUFFER_SIZE**: Define at compile time. Larger values mean fewer syscalls but use more stack memory. The 42 standard is typically 42 or similar small values for testing.
- **Return Value**: The function returns `NULL` when EOF is reached or an error occurs. The caller must distinguish between them if needed.
- **File Descriptors**: Works with any valid FD (files, stdin, pipes, sockets).

## Project Structure

```text
.
├── README.md
├── get_next_line.c
├── get_next_line_utils.c
├── get_next_line.h
├── get_next_line_bonus.c
├── get_next_line_utils_bonus.c
└── get_next_line_bonus.h
```

## Future Improvements

- Add an automated test suite for edge cases and regression checks
- Add CI to compile with multiple `BUFFER_SIZE` values
- Add performance comparisons for different buffer strategies
- Add memory-check scripts (Valgrind) as a documented workflow

## What I Learned

- Designing stateful C functions with static storage
- Building robust file-descriptor read loops around partial reads
- Managing dynamic memory safely across success and failure paths
- Structuring low-level C code into focused, reusable modules


