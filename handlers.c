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

	padding = flags->width - len;
	if (write_padding(padding, count) == -1)
		return (-1);

	return (write_string(str, count));
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
	int is_neg = 0;
	int len, padding;
	char sign_char = 0;

	if (flags->long_num)
		num = va_arg(args, long int);
	else if (flags->short_num)
		num = (short)va_arg(args, int);
	else
		num = va_arg(args, int);

	if (num < 0)
	{
		is_neg = 1;
		n = (unsigned long int)-num;
	}
	else
	{
		n = (unsigned long int)num;
	}

	sign_char = get_sign_char(is_neg, flags);

	len = get_num_len(n, 10);
	if (sign_char)
		len++;

	padding = flags->width - len;
	if (write_padding(padding, count) == -1)
		return (-1);

	if (sign_char)
	{
		if (write_char(sign_char, count) == -1)
			return (-1);
	}

	return (write_unsigned_base(n, 10, 0, count));
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

	(void)flags;
	if (!str)
		return (write_string("(null)", count));

	while (str[i])
	{
		c = (unsigned char)str[i];
		/* Check if character is non-printable */
		if (c < 32 || c >= 127)
		{
			/* Print \x */
			if (write_char('\\', count) == -1)
				return (-1);
			if (write_char('x', count) == -1)
				return (-1);
			/* Print hex value (always 2 characters, uppercase) */
			/* Print first hex digit */
			if (write_unsigned_base((c >> 4) & 0xF, 16, 1, count) == -1)
				return (-1);
			/* Print second hex digit */
			if (write_unsigned_base(c & 0xF, 16, 1, count) == -1)
				return (-1);
		}
		else
		{
			/* Print printable character normally */
			if (write_char(c, count) == -1)
				return (-1);
		}
		i++;
	}
	return (0);
}
