# printf

Custom implementation of C's `printf` function that mimics the standard library behavior.

## Overview

This project implements a custom `_printf()` function that replicates the core functionality of the standard C library's `printf()`. The implementation uses a buffered output architecture with a handler dispatch pattern for format specifiers.

## Features

### Supported Format Specifiers

- `%c` - Character
- `%s` - String
- `%d`, `%i` - Signed decimal integer
- `%u` - Unsigned decimal integer
- `%o` - Unsigned octal
- `%x` - Unsigned hexadecimal (lowercase)
- `%X` - Unsigned hexadecimal (uppercase)
- `%b` - Unsigned binary
- `%p` - Pointer address
- `%S` - String with non-printable characters as `\xXX`
- `%%` - Literal percent sign

### Supported Flags

- `+` - Forces to precede the result with a plus or minus sign (+ or -) even for positive numbers.
- `space` - If no sign is going to be written, a blank space is inserted before the value.
- `#` - Used with o, x or X specifiers the value is preceded with 0, 0x or 0X respectively, for values different than zero.

### Length Modifiers

- `l` - Applies to: `d`, `i`, `u`, `o`, `x`, `X` (long int / unsigned long int)
- `h` - Applies to: `d`, `i`, `u`, `o`, `x`, `X` (short int / unsigned short int)

### Width and Precision

- **Width**: Minimum number of characters to be printed. If the value to be printed is shorter than this number, the result is padded with blank spaces. The value is not truncated even if the result is larger.
- **Precision**:
  - For integer specifiers (`d`, `i`, `u`, `o`, `x`, `X`): Minimum number of digits to be written. If the value to be written is shorter than this number, the result is padded with leading zeros. The value is not truncated even if the result is longer.
  - For `s`: Maximum number of characters to be printed.
  - For `*`: Both width and precision can be specified as an argument using `*`.

### Special Behaviors

- NULL strings print as `(null)`
- NULL pointers print as `(nil)`
- Unknown specifiers print literally (e.g., `%r` → `%r`)
- Length modifiers are ignored for unknown specifiers (e.g., `%hZ` → `%Z`)
- Non-printable characters in `%S` displayed as `\xXX` in uppercase hex

## Project Structure

```text
├── _printf.c           # Main function and format string parser
├── handlers.c          # Basic format specifier handlers
├── handlers_numeric.c  # Numeric conversion handlers
├── handlers_pointer.c  # Pointer handler
├── utils.c            # Buffered I/O utilities
├── utils_2.c          # Numeric formatting helpers
├── main.h             # Header file with function prototypes
└── test_main/         # Test files (optional)
```

## Building

Compile with:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 -Wno-format \
    _printf.c handlers.c handlers_numeric.c handlers_pointer.c utils.c utils_2.c test_main/main.c \
    -o a.out
```

## Testing

Run the compiled program:

```bash
./a.out
```

The test files  can compare `_printf()` output with standard `printf()` to verify correctness.

## Style Compliance

This project follows the Betty coding style for C. Check compliance with (after betty installation):

```bash
betty *.c *.h
```

## Technical Details

- **Buffered I/O**: Uses a 1024-byte static buffer for efficient output
- **Handler Dispatch**: Format specifiers mapped to handler functions via lookup table
- **GNU89 Standard**: Written in C89 with GNU extensions
- **Error Handling**: Returns -1 on failure, character count on success
