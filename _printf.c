#include "main.h"

/**
 * _printf - custom-made printf implementation
 * @format: format string
 *
 * Return: number of bytes written
 */

int _printf(const char *format, ...)
{
	va_list ap;
	int f_idx = 0, printed = 0;

	if (!format)
		return (-1);
	va_start(ap, format);

	while (format[f_idx])
	{
		if (format[f_idx] == '%')
		{
			if (!format[f_idx + 1]) /* if % is the last char */
				return (-1);
			printed += handle_format(format[++f_idx], ap);
			f_idx++;
		}
		else
			printed += _putchar(format[f_idx++]);
	}
	va_end(ap);
	return (printed);
}

/**
 * handle_format - handles the format specifier(s)
 * @c: format specifier
 * @ap: va_list
 *
 * Return: number of bytes written
 */
int handle_format(const char c, va_list ap)
{
	int printed = 0, f_idx = 0;
	format_t formats[] = {
		{'c', print_char}, {'%', print_percent},
		{'s', print_string}, {'d', print_number},
		{'i', print_number}, {'b', print_binary},
		{0, NULL}
	};

	while (formats[f_idx].c)
	{
		if (c == formats[f_idx].c)
			return (formats[f_idx].f(ap));
		f_idx++;
	}
	/* if no match is found */
	printed += _putchar('%');
	printed += _putchar(c);

	return (printed);
}
