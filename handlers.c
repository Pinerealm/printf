#include "main.h"

/**
 * handle_char - writes a single character argument
 * @args: variadic list
 * @count: pointer to printed characters count
 *
 * Return: 0 on success, -1 on failure
 */
int handle_char(va_list args, int *count)
{
	char c = (char)va_arg(args, int);

	return (write_char(c, count));
}

/**
 * handle_string - writes a string argument
 * @args: variadic list
 * @count: pointer to printed characters count
 *
 * Return: 0 on success, -1 on failure
 */
int handle_string(va_list args, int *count)
{
	char *str = va_arg(args, char *);

	return (write_string(str, count));
}

/**
 * handle_percent - writes a literal percent sign
 * @args: variadic list (unused)
 * @count: pointer to printed characters count
 *
 * Return: 0 on success, -1 on failure
 */
int handle_percent(va_list args, int *count)
{
	(void)args;
	return (write_char('%', count));
}

/**
 * handle_int - writes a signed decimal integer
 * @args: variadic list
 * @count: pointer to printed characters count
 *
 * Return: 0 on success, -1 on failure
 */
int handle_int(va_list args, int *count)
{
	int num = va_arg(args, int);

	return (write_number((long)num, count));
}

/**
 * handle_string_special - writes a string with non-printable chars as \xXX
 * @args: variadic list
 * @count: pointer to printed characters count
 *
 * Return: 0 on success, -1 on failure
 */
int handle_string_special(va_list args, int *count)
{
	char *str = va_arg(args, char *);
	unsigned char c;
	int i = 0;

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
