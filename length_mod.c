#include "main.h"

/**
 * get_length_mod - calculates the length modifier
 *
 * @format: format specifier string
 * @i: pointer to the current index in the format string
 *
 * Return: length modifier
 */
int get_length_mod(const char *format, int *i)
{
	int curr_idx = *i + 1;
	int length_mod = 0;

	if (format[curr_idx] == 'l')
		length_mod = LONG_SPEC;
	else if (format[curr_idx] == 'h')
		length_mod = SHORT_SPEC;

	if (length_mod == 0)
		*i = curr_idx - 1;
	else
		*i = curr_idx;

	return (length_mod);
}
