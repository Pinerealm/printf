#include "main.h"

/**
 * print_binary_helper - helper function for print_binary function
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
 * print_decimal_helper - helper function for print_decimal function
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
 * print_octal_helper - helper for print_octal function
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
