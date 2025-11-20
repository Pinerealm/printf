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
 * write_padding - writes padding spaces
 * @padding: number of spaces to write
 * @count: pointer to printed characters count
 *
 * Return: 0 on success, -1 on failure
 */
int write_padding(int padding, int *count)
{
	while (padding > 0)
	{
		if (write_char(' ', count) == -1)
			return (-1);
		padding--;
	}
	return (0);
}

/**
 * get_sign_char - determines the sign character based on flags and value
 * @is_neg: whether the number is negative
 * @flags: active flags
 *
 * Return: sign character or 0
 */
char get_sign_char(int is_neg, flags_t *flags)
{
	if (is_neg)
		return ('-');
	if (flags->plus)
		return ('+');
	if (flags->space)
		return (' ');
	return (0);
}
