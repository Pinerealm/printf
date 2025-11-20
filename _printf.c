#include "main.h"

static int process_specifier(const char *format, int *index,
		va_list args, int *count);
static int (*get_spec_handler(char spec))(va_list, flags_t *, int *);
static void parse_flags(const char *format, int *i, flags_t *flags);

/**
 * _printf - custom printf implementation
 * @format: format string
 *
 * Return: number of characters printed or -1 on failure
 */
int _printf(const char *format, ...)
{
	va_list args;
	int count = 0, f_idx = 0;

	if (!format)
		return (-1);

	va_start(args, format);
	while (format[f_idx])
	{
		if (format[f_idx] == '%')
		{
			if (process_specifier(format, &f_idx, args, &count) == -1)
			{
				va_end(args);
				return (-1);
			}
		}
		else if (write_char(format[f_idx], &count) == -1)
		{
			va_end(args);
			return (-1);
		}
		f_idx++;
	}
	if (flush_buffer(&count) == -1)
	{
		va_end(args);
		return (-1);
	}
	va_end(args);
	return (count);
}

/**
 * parse_flags - parses flags, width, and length modifiers
 * @format: format string
 * @i: current index in format string
 * @flags: flags struct to populate
 */
static void parse_flags(const char *format, int *i, flags_t *flags)
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
		else
			break;
		(*i)++;
	}

	/* Parse width */
	while (format[*i] >= '0' && format[*i] <= '9')
	{
		flags->width = flags->width * 10 + (format[*i] - '0');
		(*i)++;
	}

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
static int process_specifier(const char *format, int *index,
		va_list args, int *count)
{
	int (*handler)(va_list, flags_t *, int *);
	flags_t flags = {0, 0, 0, 0, 0, 0};
	int i = *index + 1;

	parse_flags(format, &i, &flags);

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
		{'X', handle_hex_upper}
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
