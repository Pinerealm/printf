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
	int printed = 0;

	switch (c)
	{
		case 'c':
			printed += _putchar(va_arg(ap, int));
			break;
		case 's':
			printed += print_string(va_arg(ap, char *));
			break;
		case '%':
			printed += _putchar('%');
			break;
		case 'd':
		case 'i':
			printed += print_number(va_arg(ap, int));
			break;
		case 'b':
			printed += print_binary(va_arg(ap, unsigned long int));
			break;
		default:
			printed += _putchar('%');
			printed += _putchar(c);
			break;
	}
	return (printed);
}

/**
 * print_string - prints a string
 * @str: string to print
 *
 * Return: number of bytes written
 */
int print_string(char *str)
{
	int printed = 0, idx = 0;
	char *buf = str;

	if (!buf)
		buf = "(null)";
	while (buf[idx])
		printed += _putchar(buf[idx++]);
	return (printed);
}

/**
 * print_number - prints an integer
 * @n: integer to print
 *
 * Return: number of bytes written
 */
int print_number(int n)
{
	unsigned int num;
	int printed = 0;

	if (n < 0)
	{
		printed += _putchar('-');
		n = -n;
	}
	num = n;
	if (num / 10 == 0)
		printed += _putchar(num + '0');
	else
	{
		printed += print_number(num / 10);
		printed += _putchar(num % 10 + '0');
	}
	return (printed);
}

/**
 * print_binary - prints a number in binary
 * @n: number to print
 *
 * Return: number of bytes written
 */
int print_binary(unsigned int n)
{
	int printed = 0;
	unsigned long int num = (unsigned long int)n;

	if (num / 2)
		print_binary(num / 2);
	if (num == 0)
		printed += _putchar('0');
	printed += _putchar(num % 2 + '0');

	return (printed);
}
