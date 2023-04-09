#include "main.h"

/**
 * print_string - prints a string
 * @ap: pointer to the argument list
 *
 * Return: number of bytes written
 */
int print_string(va_list ap)
{
	int printed = 0, idx = 0;
	char *buf = va_arg(ap, char *);

	if (!buf)
		buf = "(null)";
	while (buf[idx])
		printed += _putchar(buf[idx++]);
	return (printed);
}

/**
 * print_decimal - prints a number as a signed decimal
 * @ap: pointer to the argument list
 *
 * Return: number of bytes written
 */
int print_decimal(va_list ap)
{
	int n = va_arg(ap, int), printed = 0;
	unsigned int num;

	if (n < 0)
	{
		printed += _putchar('-');
		n = -n;
	}
	num = n;
	return (printed + print_decimal_helper(num));
}

/**
 * print_binary - prints a number in binary
 * @ap: pointer to the argument list
 *
 * Return: number of bytes written
 */
int print_binary(va_list ap)
{
	unsigned int n = va_arg(ap, unsigned int);

	return (print_binary_helper(n));
}

/**
 * print_char - prints a character
 * @ap: pointer to the argument list
 *
 * Return: number of bytes written
 */
int print_char(va_list ap)
{
	return (_putchar(va_arg(ap, int)));
}

/**
 * print_percent - prints a percent sign
 * @ap: pointer to the argument list
 *
 * Return: number of bytes written
 */
int print_percent(va_list ap)
{
	(void)ap;
	return (_putchar('%'));
}
