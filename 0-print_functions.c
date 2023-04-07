#include "main.h"

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
	if (num / 10)
		printed += print_number(num / 10);
	printed += _putchar(num % 10 + '0');

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

	if (n > 1)
		printed += print_binary(n >> 1);
	printed += _putchar((n & 1) + '0');

	return (printed);
}
