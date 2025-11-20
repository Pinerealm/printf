#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

/**
 * struct flags - flags to turn on
 * @plus: flag for '+'
 * @space: flag for ' '
 * @hash: flag for '#'
 */
typedef struct flags
{
	int plus;
	int space;
	int hash;
} flags_t;

/**
 * struct spec_handler - maps a specifier to its handler
 * @spec: the conversion specifier character
 * @handler: pointer to the handler function
 */
typedef struct spec_handler
{
	char spec;
	int (*handler)(va_list args, flags_t *flags, int *count);
} spec_handler_t;

int _printf(const char *format, ...);
int flush_buffer(int *count);

int write_char(char c, int *count);
int write_string(const char *str, int *count);
int write_number(long num, int *count);
int write_unsigned_base(unsigned long int num, unsigned int base,
		int uppercase, int *count);

int handle_char(va_list args, int *count);
int handle_string(va_list args, int *count);
int handle_percent(va_list args, int *count);
int handle_int(va_list args, int *count);

int handle_binary(va_list args, int *count);
int handle_unsigned(va_list args, int *count);
int handle_octal(va_list args, int *count);
int handle_hex_lower(va_list args, int *count);

int handle_hex_upper(va_list args, int *count);
int handle_string_special(va_list args, int *count);
int handle_pointer(va_list args, int *count);

#endif /* MAIN_H */
