#include "main.h"

static int (*get_spec_handler(char spec))(va_list, flags_t *, int *);
static void parse_flags(const char *format, int *i, flags_t *flags,
		va_list args);
static void parse_width(const char *format, int *i, flags_t *flags,
		va_list args);
static void parse_precision(const char *format, int *i, flags_t *flags,
		va_list args);

/**
 * parse_width - parses the field width
 * @format: format string
 * @i: current index in format string
 * @flags: flags struct to populate
 * @args: variadic arguments list
 */
static void parse_width(const char *format, int *i, flags_t *flags,
		va_list args)
{
	if (format[*i] == '*')
	{
		int w = va_arg(args, int);

		flags->width = w;
		if (w < 0)
		{
			flags->width = -w;
			flags->minus = 1;
		}
		(*i)++;
	}
	else
	{
		while (format[*i] >= '0' && format[*i] <= '9')
		{
			flags->width = flags->width * 10 + (format[*i] - '0');
			(*i)++;
		}
	}
}

/**
 * parse_precision - parses the precision
 * @format: format string
 * @i: current index in format string
 * @flags: flags struct to populate
 * @args: variadic arguments list
 */
static void parse_precision(const char *format, int *i, flags_t *flags,
		va_list args)
{
	if (format[*i] == '.')
	{
		(*i)++;
		if (format[*i] == '*')
		{
			int p = va_arg(args, int);

			flags->precision = (p < 0) ? -1 : p;
			(*i)++;
		}
		else
		{
			flags->precision = 0;
			while (format[*i] >= '0' && format[*i] <= '9')
			{
				flags->precision = flags->precision * 10 + (format[*i] - '0');
				(*i)++;
			}
		}
	}
}

/**
 * parse_flags - parses flags, width, and length modifiers
 * @format: format string
 * @i: current index in format string
 * @flags: flags struct to populate
 * @args: variadic arguments list
 */
static void parse_flags(const char *format, int *i, flags_t *flags,
		va_list args)
{
	/* Parse flags */
	while (format[*i])
	{
		if (format[*i] == '+')
			flags->plus = 1;
		else if (format[*i] == ' ')
			flags->space = 1;
		else if (format[*i] == '#')
			flags->hash = 1;
		else if (format[*i] == '0')
			flags->zero = 1;
		else if (format[*i] == '-')
			flags->minus = 1;
		else
			break;
		(*i)++;
	}

	parse_width(format, i, flags, args);
	parse_precision(format, i, flags, args);

	/* Parse length modifiers */
	if (format[*i] == 'l')
	{
		flags->long_num = 1;
		(*i)++;
	}
	else if (format[*i] == 'h')
	{
		flags->short_num = 1;
		(*i)++;
	}
}

/**
 * process_specifier - handles a percent sequence inside the format
 * @format: format string being parsed
 * @index: pointer to the current index within the string
 * @args: variadic arguments list
 * @count: pointer to printed characters count
 *
 * Return: 0 on success, -1 on failure
 */
int process_specifier(const char *format, int *index,
		va_list args, int *count)
{
	int (*handler)(va_list, flags_t *, int *);
	flags_t flags = {0, 0, 0, 0, 0, 0, 0, 0, -1};
	int i = *index + 1;

	parse_flags(format, &i, &flags, args);

	if (format[i] == '\0')
		return (-1);

	handler = get_spec_handler(format[i]);
	if (handler)
	{
		*index = i;
		return (handler(args, &flags, count));
	}

	if (write_char('%', count) == -1)
		return (-1);

	/* Print the flags and the character that caused the mismatch */
	while (*index < i)
	{
		(*index)++;
		if (format[*index] == 'l' || format[*index] == 'h')
			continue;
		if (write_char(format[*index], count) == -1)
			return (-1);
	}
	return (0);
}

/**
 * get_spec_handler - retrieves a handler for a specifier
 * @spec: conversion specifier character
 *
 * Return: pointer to handler function or NULL if unsupported
 */
static int (*get_spec_handler(char spec))(va_list, flags_t *, int *)
{
	spec_handler_t handlers[] = {
		{'c', handle_char},
		{'s', handle_string},
		{'S', handle_string_special},
		{'p', handle_pointer},
		{'%', handle_percent},
		{'d', handle_int},
		{'i', handle_int},
		{'b', handle_binary},
		{'u', handle_unsigned},
		{'o', handle_octal},
		{'x', handle_hex_lower},
		{'X', handle_hex_upper},
		{'r', handle_reversed}
	};
	int i;
	int handler_count = sizeof(handlers) / sizeof(handlers[0]);

	for (i = 0; i < handler_count; i++)
	{
		if (handlers[i].spec == spec)
			return (handlers[i].handler);
	}
	return (0);
}
