#include "main.h"

/**
 * handle_char - writes a single character argument
 * @args: variadic list
 * @flags: active flags
 * @count: pointer to printed characters count
 *
 * Return: 0 on success, -1 on failure
 */
int handle_char(va_list args, flags_t *flags, int *count)
{
	char c = (char)va_arg(args, int);
	int padding = flags->width - 1;

	if (write_padding(padding, count) == -1)
		return (-1);

	return (write_char(c, count));
}

/**
 * handle_string - writes a string argument
 * @args: variadic list
 * @flags: active flags
 * @count: pointer to printed characters count
 *
 * Return: 0 on success, -1 on failure
 */
int handle_string(va_list args, flags_t *flags, int *count)
{
	char *str = va_arg(args, char *);
	int len = 0, padding;

	if (!str)
		str = "(null)";

	while (str[len])
		len++;

	if (flags->precision >= 0 && flags->precision < len)
		len = flags->precision;

	padding = flags->width - len;
	if (write_padding(padding, count) == -1)
		return (-1);

	return (write_string_len(str, len, count));
}

/**
 * handle_percent - writes a literal percent sign
 * @args: variadic list (unused)
 * @flags: active flags
 * @count: pointer to printed characters count
 *
 * Return: 0 on success, -1 on failure
 */
int handle_percent(va_list args, flags_t *flags, int *count)
{
	(void)args;
	(void)flags;
	return (write_char('%', count));
}

/**
 * handle_int - writes a signed decimal integer
 * @args: variadic list
 * @flags: active flags
 * @count: pointer to printed characters count
 *
 * Return: 0 on success, -1 on failure
 */
int handle_int(va_list args, flags_t *flags, int *count)
{
	long num;
	unsigned long int n;
	int is_neg, len, padding, zeros = 0;
	char sign_char;

	if (flags->long_num)
		num = va_arg(args, long int);
	else
		num = flags->short_num ? (short)va_arg(args, int) : va_arg(args, int);

	is_neg = (num < 0);
	n = is_neg ? (unsigned long int)-num : (unsigned long int)num;
	len = (n == 0 && flags->precision == 0) ? 0 : get_num_len(n, 10);
	zeros = (flags->precision > len) ? flags->precision - len : 0;
	sign_char = get_sign_char(is_neg, flags);
	padding = flags->width - (len + zeros + (sign_char ? 1 : 0));

	if (write_padding(padding, count) == -1)
		return (-1);

	if (sign_char && write_char(sign_char, count) == -1)
		return (-1);

	while (zeros > 0)
	{
		if (write_char('0', count) == -1)
			return (-1);
		zeros--;
	}

	if (len > 0)
		return (write_unsigned_base(n, 10, 0, count));
	return (0);
}

/**
 * handle_string_special - writes a string with non-printable chars as \xXX
 * @args: variadic list
 * @flags: active flags
 * @count: pointer to printed characters count
 *
 * Return: 0 on success, -1 on failure
 */
int handle_string_special(va_list args, flags_t *flags, int *count)
{
	char *str = va_arg(args, char *);
	unsigned char c;
	int i = 0;
	const char *hex = "0123456789ABCDEF";

	(void)flags;
	if (!str)
		return (write_string_len("(null)", 6, count));

	while (str[i])
	{
		c = (unsigned char)str[i];
		if (c < 32 || c >= 127)
		{
			if (write_char('\\', count) == -1 || write_char('x', count) == -1 ||
			    write_char(hex[(c >> 4) & 0xF], count) == -1 ||
			    write_char(hex[c & 0xF], count) == -1)
				return (-1);
		}
		else
		{
			if (write_char(c, count) == -1)
				return (-1);
		}
		i++;
	}
	return (0);
}
