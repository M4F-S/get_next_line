# Get Next Line

*This project has been created as part of the 42 curriculum by mfathy.*

## Description

Get_next_line is a function that reads a file line by line. Simple as that. You call it once, you get one line. Call it again, you get the next line. Keep calling until there's nothing left to read.

The catch? The function needs to work with different buffer sizes (set at compile time), handle weird edge cases, and not leak memory. It's basically teaching you how to manage file reading with static variables and dynamic memory allocation.

What it does:
- Returns one line at a time from a file descriptor
- Includes the newline character (unless it's the last line without one)
- Returns NULL when the file is done or something goes wrong
- Works with stdin, files, or any valid file descriptor

## Instructions

### How to compile
Bash

# Basic compilation
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c your_main.c

# Test with tiny buffer (harder test)
cc -Wall -Wextra -Werror -D BUFFER_SIZE=1 get_next_line.c get_next_line_utils.c your_main.c


### Basic usage

#include "get_next_line.h"
#include <fcntl.h>

int main(void)
{
    int fd = open("file.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)))
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
}

### Check for leaks

valgrind --leak-check=full ./test

## Algorithm Explanation

I went with a static buffer approach that accumulates data until it finds a newline.

### How it works:

1. Keep a static buffer that survives between function calls
2. Read chunks of BUFFER_SIZE bytes into a temporary buffer
3. Append each chunk to the static buffer
4. Once we find a \n, extract everything up to (and including) it
5. Save the rest for the next call

### Why this approach?

I considered a few options:
- Read the whole file then split: Nope, too memory hungry and against the rules
- Read character by character: Way too slow, would make BUFFER_SIZE pointless
- This accumulation method: Clean, handles any line length, works with any buffer size

The key insight is using a static variable to "remember" what we've read. The buffer grows as needed, and we only extract lines when we find a newline (or hit EOF).

Pros:
- Simple logic, easy to debug
- Memory efficient (only keeps what's needed)
- Handles all edge cases naturally
- Works with BUFFER_SIZE from 1 to millions

Cons:
- One malloc per read cycle (acceptable trade-off for simplicity)
- Static variable means one buffer per FD in mandatory (bonus fixes this)

## Resources

### What I used to learn this stuff:

Documentation:
- Linux man pages for read() - essential for understanding the system call
- GeeksforGeeks articles on static variables and file I/O

Testing:
- [Tripouille's gnlTester](https://github.com/Tripouille/gnlTester) - helped catch edge cases
- Made my own test file (https://github.com/M4F-S/get_next_line-_tester_berlin_2025/tree/main)

### AI Usage:

I used Perplexity and Co-pilot to:
- Understand how static variables work between function calls
- Learn about pointer-to-pointer patterns for modifying the buffer
- Generate test cases I might have missed
- Debug memory management issues
- Used to reorganize and rewite the readme.md file 

Everything was coded by hand though. AI was just for explaining concepts and suggesting what to test, not for writing the actual code. I made sure to understand every line before implementing it.

The trickiest part was handling the buffer extraction without memory leaks - took a lot of trial and error even after understanding the concept.

## Files

- get_next_line.h - header with prototypes
- get_next_line.c - main function
- get_next_line_utils.c - helper functions (strlen, strchr, strjoin, etc.)
- main.c - comprehensive test suite

## Testing Notes

The function should pass with:
- Empty files
- Files with no newline at the end
- Very long lines (bigger than BUFFER_SIZE)
- Multiple empty lines
- BUFFER_SIZE = 1 (the ultimate stress test)


