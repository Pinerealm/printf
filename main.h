#ifndef MAIN_H
#define MAIN_H
#include <stdlib.h>
#include <stdarg.h>

int _printf(const char *format, ...);
int _putchar(char c);
int handle_format(const char c, va_list ap);
int print_string(char *str);

int print_number(int n);
int print_binary(unsigned int n);

#endif /* MAIN_H */
