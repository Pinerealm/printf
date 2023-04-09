#include "main.h"

/**
 * print_binary_helper - helper for the print_binary function
 * @n: number to print
 *
 * Return: number of bytes written
 */
int print_binary_helper(unsigned int n)
{
	int printed = 0;

	if (n > 1)
		printed += print_binary_helper(n >> 1);
	printed += _putchar((n & 1) + '0');

	return (printed);
}

/**
 * print_decimal_helper - helper for the print_decimal function
 * @n: number to print
 *
 * Return: number of bytes written
 */
int print_decimal_helper(unsigned int n)
{
	int printed = 0;

	if (n / 10)
		printed += print_decimal_helper(n / 10);
	printed += _putchar(n % 10 + '0');

	return (printed);
}

/**
 * print_octal_helper - helper for the print_octal function
 * @n: number to print
 *
 * Return: number of bytes written
 */
int print_octal_helper(unsigned int n)
{
	int printed = 0;

	if (n / 8)
		printed += print_octal_helper(n / 8);
	printed += _putchar(n % 8 + '0');

	return (printed);
}

/**
 * print_hex_helper - helper for the print_hex function
 * @n: number to print
 *
 * Return: number of bytes written
 */
int print_hex_helper(unsigned int n)
{
	int printed = 0;

	if (n / 16)
		printed += print_hex_helper(n / 16);
	if (n % 16 < 10)
		printed += _putchar(n % 16 + '0');
	else
		printed += _putchar(n % 16 - 10 + 'a');

	return (printed);
}

/**
 * print_hex_upper_helper - helper for the print_hex_upper function
 * @n: number to print
 *
 * Return: number of bytes written
 */
int print_hex_upper_helper(unsigned int n)
{
	int printed = 0;

	if (n / 16)
		printed += print_hex_upper_helper(n / 16);
	if (n % 16 < 10)
		printed += _putchar(n % 16 + '0');
	else
		printed += _putchar(n % 16 - 10 + 'A');

	return (printed);
}
