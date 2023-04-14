#include "main.h"

/**
 * print_octal - prints a number as an unsigned octal
 * @ap: pointer to the argument list
 *
 * Return: number of bytes written
 */
int print_octal(va_list ap)
{
	unsigned int n = va_arg(ap, unsigned int);
	int printed = 0;

	if (n == 0)
		return (_putchar('0'));
	return (printed + print_octal_helper(n));
}

/**
 * print_unsigned_decimal - prints a number as an unsigned decimal
 * @ap: pointer to the argument list
 *
 * Return: number of bytes written
 */
int print_unsigned_decimal(va_list ap)
{
	unsigned int n = va_arg(ap, unsigned int);
	int printed = 0;

	if (n == 0)
		return (_putchar('0'));
	return (printed + print_decimal_helper(n));
}

/**
 * print_hex - prints a number as an unsigned hexadecimal
 * @ap: pointer to the argument list
 *
 * Return: number of bytes written
 */
int print_hex(va_list ap)
{
	unsigned int n = va_arg(ap, unsigned int);
	int printed = 0;

	if (n == 0)
		return (_putchar('0'));
	return (printed + print_hex_helper(n));
}

/**
 * print_hex_upper - prints a number as an unsigned hexadecimal with
 * uppercase letters
 * @ap: pointer to the argument list
 *
 * Return: number of bytes written
 */
int print_hex_upper(va_list ap)
{
	unsigned int n = va_arg(ap, unsigned int);
	int printed = 0;

	if (n == 0)
		return (_putchar('0'));
	return (printed + print_hex_upper_helper(n));
}

/**
 * print_string_ascii - prints a string with non-printable characters
 * replaced by \x followed by the ASCII code in hexadecimal
 * @ap: pointer to the argument list
 *
 * Return: number of bytes written
 */
int print_string_ascii(va_list ap)
{
	char *s = va_arg(ap, char *);
	int printed = 0;

	if (s == NULL)
		s = "(null)";
	while (*s)
	{
		if (*s < 32 || *s >= 127)
		{
			printed += write(1, "\\x", 2);
			printed += print_hex_upper_helper(*s);
		}
		else
			printed += _putchar(*s);
		s++;
	}
	return (printed);
}
