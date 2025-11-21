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
		if (prefix)
		{
			int i = 0;

			while (prefix[i])
			{
				if (write_char(prefix[i], count) == -1)
					return (-1);
				i++;
			}
		}
		if (write_chars('0', padding, count) == -1)
			return (-1);
	}
	else
	{
		if (write_chars(' ', padding, count) == -1)
			return (-1);
		if (prefix)
		{
			int i = 0;

			while (prefix[i])
			{
				if (write_char(prefix[i], count) == -1)
					return (-1);
				i++;
			}
		}
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

/**
 * write_unsigned_base - writes an unsigned number in any base
 * @num: number to write
 * @base: base between 2 and 16
 * @uppercase: non-zero for uppercase digits
 * @count: pointer to printed characters count
 *
 * Return: 0 on success, -1 on failure
 */
int write_unsigned_base(unsigned long int num, unsigned int base,
		int uppercase, int *count)
{
	const char *digits_lower = "0123456789abcdef";
	const char *digits_upper = "0123456789ABCDEF";
	const char *digits;

	if (base < 2 || base > 16)
		return (-1);

	digits = uppercase ? digits_upper : digits_lower;

	if (num >= base)
	{
		if (write_unsigned_base(num / base, base, uppercase, count) == -1)
			return (-1);
	}
	return (write_char(digits[num % base], count));
}
