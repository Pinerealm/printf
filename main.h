#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

int _printf(const char *format, ...);
int _putchar(char c);
int print_char(va_list ap);
int print_string(va_list ap);
int print_number(int n);
int char_num_handler(const char c, va_list ap);
int num_to_string(va_list vl, const char c);

#endif /* MAIN_H */
