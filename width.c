#include "main.h"

/**
 * get_width - calculates the field width specified by the format specifier
 *
 * @format: format specifier string.
 * @i: pointer to the current format string index.
 * @ap: pointer to the va_list variable.
 *
 * Return: width.
 */
int get_width(const char *format, int *i, va_list ap)
{
	int curr_idx, width = 0;

	for (curr_idx = *i + 1; format[curr_idx]; curr_idx++)
	{
		if (is_digit(format[curr_idx]))
		{
			width *= 10;
			width += format[curr_idx] - '0';
		}
		else if (format[curr_idx] == '*')
		{
			curr_idx++;
			width = va_arg(ap, int);
			break;
		}
		else
			break;
	}

	*i = curr_idx - 1;

	return (width);
}
