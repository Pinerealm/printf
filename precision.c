#include "main.h"

/**
 * get_precision - calculates the precision for real numbers.
 *
 * @format: format specifier string
 * @i: pointer to the current format string index
 * @ap: pointer to the va_list variable.
 *
 * Return: precision.
 */

int get_precision(const char *format, int *i, va_list ap)
{
	int curr_idx = *i + 1;
	int precision = 0;

	if (format[curr_idx] != '.')
		return (-1);

	for (curr_idx += 1; format[curr_idx]; curr_idx++)
	{
		if (is_digit(format[curr_idx]))
		{
			precision *= 10;
			precision += format[curr_idx] - '0';
		}
		else if (format[curr_idx] == '*')
		{
			curr_idx++;
			precision = va_arg(ap, int);
			break;
		}
		else
			break;
	}

	*i = curr_idx - 1;

	return (precision);
}
