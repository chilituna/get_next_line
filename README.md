# get_next_line

A robust C implementation of `get_next_line(int fd)`, a function that reads from a file descriptor and returns one line at a time.

This project was completed as part of the 42 curriculum and includes both the mandatory version and the bonus version (simultaneous handling of multiple file descriptors).

Grade: `125/100`

## About

This repository showcases practical C systems-programming fundamentals: precise control over memory, file-descriptor I/O, and predictable behavior under constrained APIs.

## Project Summary

`get_next_line` solves a common systems-programming task: incremental line-by-line reading from streams without loading the entire file into memory.

The function:
- Returns the next line from a file descriptor, including the trailing `\n` when present.
- Preserves unread content between calls using static storage.
- Returns `NULL` on end-of-file or error.

## Technical Highlights

- Built with low-level POSIX I/O (`read`) and manual memory management.
- Supports configurable read chunk size through `BUFFER_SIZE`.
- Handles partial reads and line reconstruction across multiple buffers.
- Includes custom string utilities (`ft_strlen`, `ft_strjoin`, `ft_substr`, etc.) to avoid external dependencies.
- Bonus implementation supports parallel reads across many FDs via static per-FD storage.

## Repository Structure

- `get_next_line.c`: mandatory `get_next_line` implementation
- `get_next_line_utils.c`: mandatory helper/string utility functions
- `get_next_line.h`: mandatory header and prototypes
- `get_next_line_bonus.c`: bonus implementation for multiple file descriptors
- `get_next_line_utils_bonus.c`: bonus helper/string utility functions
- `get_next_line_bonus.h`: bonus header and prototypes

## Build

Compile the mandatory version:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
```

Compile the bonus version:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c
```

Notes:
- Define `BUFFER_SIZE` at compile time based on your test scenario.
- Typical 42 integration links these files with a separate `main.c` test file.

## API

Prototype:

```c
char *get_next_line(int fd);
```

Behavior:
- Input: valid file descriptor.
- Output: dynamically allocated string containing one line.
- Return values:
  - non-`NULL`: next line (caller must `free` it)
  - `NULL`: EOF reached or read/allocation error

## Example Usage

```c
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "get_next_line.h"

int main(void)
{
	int fd = open("example.txt", O_RDONLY);
	char *line;

	if (fd < 0)
		return (1);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
```

## Skills Demonstrated

- Memory-safe dynamic allocation and cleanup paths
- Stateful function design with static variables
- Stream processing and buffer-based parsing
- Edge-case handling (EOF, empty input, invalid FDs, read errors)
- Writing reusable low-level utility functions in C


