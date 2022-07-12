#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>

int _printf(const char *format, ...);
int _putchar(char c);
int print_char(va_list ap);
int print_string(va_list ap);
int print_number(int n);
int char_num_handler(const char c, va_list ap);

#endif /* MAIN_H */
