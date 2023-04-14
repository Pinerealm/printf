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
	unsigned int f_idx = 0, b_idx = 0;
	long printed = 0;
	char l_buf[BUFFER_SIZE];

	if (!format)
		return (-1);
	va_start(ap, format);

	while (format[f_idx])
	{
		if (b_idx == BUFFER_SIZE)
		{
			printed += print_buffer(l_buf, &b_idx);
		}
		if (format[f_idx] == '%')
		{
			if (!format[f_idx + 1]) /* if % is the last char */
				return (-1);
			printed += print_buffer(l_buf, &b_idx);
			printed += handle_format(format[++f_idx], ap);
			f_idx++;
		}
		else
			l_buf[b_idx++] = format[f_idx++];
	}
	va_end(ap);
	printed += print_buffer(l_buf, &b_idx);

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
		{'s', print_string}, {'d', print_decimal},
		{'i', print_decimal}, {'b', print_binary},
		{'o', print_octal}, {'u', print_unsigned_decimal},
		{'x', print_hex}, {'X', print_hex_upper},
		{'S', print_string_ascii}, {0, NULL}
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

/**
 * print_buffer - prints the buffer
 * @buffer: buffer to print
 * @b_idx: pointer to buffer index
 *
 * Return: number of bytes written
 */
int print_buffer(char *buffer, unsigned int *b_idx)
{
	ssize_t written = write(1, buffer, *b_idx);

	*b_idx = 0;
	return (written);
}
