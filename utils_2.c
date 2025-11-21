#include "main.h"

/**
 * get_num_len - calculates the length of a number in a given base
 * @num: number to calculate length for
 * @base: base of the number
 *
 * Return: length of the number
 */
int get_num_len(unsigned long int num, unsigned int base)
{
	int len = 0;

	if (num == 0)
		return (1);

	while (num > 0)
	{
		len++;
		num /= base;
	}
	return (len);
}

/**
 * write_chars - writes n characters to stdout
 * @c: character to write
 * @n: number of times to write
 * @count: pointer to printed characters count
 *
 * Return: 0 on success, -1 on failure
 */
int write_chars(char c, int n, int *count)
{
	while (n > 0)
	{
		if (write_char(c, count) == -1)
			return (-1);
		n--;
	}
	return (0);
}

/**
 * write_padded - writes padding and optional prefix
 * @padding: number of padding characters
 * @pad_char: character to use for padding (' ' or '0')
 * @prefix: optional prefix string (e.g., "0x", "+")
 * @count: pointer to printed characters count
 *
 * Return: 0 on success, -1 on failure
 */
int write_padded(int padding, char pad_char, const char *prefix, int *count)
{
	if (pad_char == '0')
	{
		if (write_string(prefix, count) == -1)
			return (-1);
		if (write_chars('0', padding, count) == -1)
			return (-1);
	}
	else
	{
		if (write_chars(' ', padding, count) == -1)
			return (-1);
		if (write_string(prefix, count) == -1)
			return (-1);
	}
	return (0);
}

/**
 * get_unsigned_val - retrieves an unsigned value based on length modifiers
 * @args: variadic list
 * @flags: active flags
 *
 * Return: the retrieved value cast to unsigned long int
 */
unsigned long int get_unsigned_val(va_list args, flags_t *flags)
{
	if (flags->long_num)
		return (va_arg(args, unsigned long int));
	if (flags->short_num)
		return ((unsigned short)va_arg(args, unsigned int));
	return (va_arg(args, unsigned int));
}
