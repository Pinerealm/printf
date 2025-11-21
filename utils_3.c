#include "main.h"

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

/**
 * write_number_left - writes a number with left alignment
 * @num: number to write
 * @base: base of the number
 * @prefix: prefix string
 * @uppercase: non-zero for uppercase digits
 * @zeros: number of zero padding
 * @padding: number of space padding
 * @len: length of the number
 * @count: pointer to printed characters count
 *
 * Return: 0 on success, -1 on failure
 */
static int write_number_left(unsigned long int num, int base, char *prefix,
		int uppercase, int zeros, int padding, int len, int *count)
{
	if (write_string(prefix, count) == -1)
		return (-1);
	if (write_chars('0', zeros, count) == -1)
		return (-1);
	if (len > 0 && write_unsigned_base(num, base, uppercase, count) == -1)
		return (-1);
	return (write_chars(' ', padding, count));
}

/**
 * write_number_right - writes a number with right alignment
 * @num: number to write
 * @base: base of the number
 * @prefix: prefix string
 * @uppercase: non-zero for uppercase digits
 * @zeros: number of zero padding
 * @padding: number of space padding
 * @pad_char: padding character
 * @len: length of the number
 * @count: pointer to printed characters count
 *
 * Return: 0 on success, -1 on failure
 */
static int write_number_right(unsigned long int num, int base, char *prefix,
		int uppercase, int zeros, int padding, char pad_char,
		int len, int *count)
{
	if (write_padded(padding, pad_char, prefix, count) == -1)
		return (-1);
	if (write_chars('0', zeros, count) == -1)
		return (-1);
	if (len > 0)
		return (write_unsigned_base(num, base, uppercase, count));
	return (0);
}

/**
 * write_number - writes a number with full formatting
 * @num: number to write
 * @flags: active flags
 * @base: base of the number
 * @prefix: prefix string (e.g., "0x", "+", "-")
 * @uppercase: non-zero for uppercase digits
 * @count: pointer to printed characters count
 *
 * Return: 0 on success, -1 on failure
 */
int write_number(unsigned long int num, flags_t *flags, int base,
		char *prefix, int uppercase, int *count)
{
	int len, padding, zeros = 0;
	char pad_char = ' ';

	if (num == 0 && flags->precision == 0)
		len = 0;
	else
		len = get_num_len(num, base);

	if (flags->precision > len)
		zeros = flags->precision - len;

	if (flags->zero && flags->precision == -1 && !flags->minus)
		pad_char = '0';

	padding = flags->width - (len + zeros);
	if (prefix)
	{
		int i = 0;

		while (prefix[i++])
			padding--;
	}

	if (flags->minus)
		return (write_number_left(num, base, prefix, uppercase, zeros,
					padding, len, count));

	return (write_number_right(num, base, prefix, uppercase, zeros,
				padding, pad_char, len, count));
}
