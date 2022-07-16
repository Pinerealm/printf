#ifndef MAIN_H
#define MAIN_H
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>


#define IGNORE(x) (void)(x)
#define BUFFER_SIZE 1024

/* FLAGS */
#define F_MINUS 1
#define F_PLUS 2
#define F_ZERO 4
#define F_HASH 8
#define F_SPACE 16

/* LENGTH MODIFIERS */
#define LONG_SPEC 2
#define SHORT_SPEC 1


/**
 * struct fmt_spec - struct for format specifier
 * @spec: format character
 * @func: function pointer that prints in specified format
 *
 * fmt_spec - typedef for struct fmt_spec
 */
typedef struct fmt_spec
{
	char spec;
	int (*func)(va_list, char *, int, int, int, int);
} fmt_spec;


/* FUNCTION DECLARATIONS */
int _printf(const char *format, ...);
void print_buf(char *buffer, int *buff_idx);
int format_printer(const char *, int *, va_list, char *, int, int, int, int);

/* Fxns to get flag, width, precision, length_mod */
int get_flag(const char *format, int *i);
int get_width(const char *, int *, va_list);
int get_precision(const char *, int *, va_list);
int get_length_mod(const char *, int *);

/* Format printer functions */
int print_char(va_list ap, char *buffer,
	int flags, int width, int precision, int length_mod);
int print_str(va_list, char *, int, int, int, int);
int print_percent(va_list, char *, int, int, int, int);

/* Format helper functions */
int handle_char(char c, char *buffer,
	int flag, int width, int precision, int length_mod);

/* Support functions */
int is_digit(char);

#endif /* MAIN_H */
