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
	int printed = 0;
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
			handle_format(format[++f_idx], ap, l_buf, &b_idx);
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
 * @buf: buffer to write to
 * @b_idx: pointer to buffer index
 *
 * Return: number of bytes written
 */
int
handle_format(const char c, va_list ap, char *buf, unsigned int *b_idx)
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

	while (formats[f_idx].spec)
	{
		if (c == formats[f_idx].spec)
			return (formats[f_idx].f(ap, buf, b_idx));
		f_idx++;
	}
	buf[(*b_idx)++] = '%';
	buf[(*b_idx)++] = c;
	printed = 2;

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
