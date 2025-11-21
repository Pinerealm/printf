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
 * @long_num: flag for 'l' length modifier
 * @short_num: flag for 'h' length modifier
 * @width: field width
 * @precision: precision specifier
 */
typedef struct flags
{
	int plus;
	int space;
	int hash;
	int zero;
	int long_num;
	int short_num;
	int width;
	int precision;
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
int write_string_len(const char *str, int len, int *count);
int write_num_full(unsigned long int num, flags_t *flags, int base,
		int uppercase, int *count);
int write_unsigned_base(unsigned long int num, unsigned int base,
		int uppercase, int *count);

int get_num_len(unsigned long int num, unsigned int base);
char get_sign_char(int is_neg, flags_t *flags);
int write_padding(int padding, int *count);

int handle_char(va_list args, flags_t *flags, int *count);
int handle_string(va_list args, flags_t *flags, int *count);
int handle_percent(va_list args, flags_t *flags, int *count);
int handle_int(va_list args, flags_t *flags, int *count);

int handle_binary(va_list args, flags_t *flags, int *count);
int handle_unsigned(va_list args, flags_t *flags, int *count);
int handle_octal(va_list args, flags_t *flags, int *count);
int handle_hex_lower(va_list args, flags_t *flags, int *count);

int handle_hex_upper(va_list args, flags_t *flags, int *count);
int handle_string_special(va_list args, flags_t *flags, int *count);
int handle_pointer(va_list args, flags_t *flags, int *count);

#endif /* MAIN_H */
