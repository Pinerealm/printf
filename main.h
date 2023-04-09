#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <stdarg.h>

/**
 * struct format - link between format specifier and function
 * @c: format specifier
 * @f: function to handle format specifier
 */
typedef struct format
{
	char c;
	int (*f)(va_list);
} format_t;

int _printf(const char *format, ...);
int _putchar(char c);
int handle_format(const char c, va_list ap);
int print_string(va_list ap);

int print_number(va_list ap);
int print_number_helper(unsigned int n);
int print_char(va_list ap);
int print_percent(va_list ap);

int print_binary(va_list ap);
int print_binary_helper(unsigned int n);

#endif /* MAIN_H */
