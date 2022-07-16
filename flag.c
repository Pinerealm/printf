#include "main.h"

/**
 * get_flag - calculates active flags
 *
 * @format: format specifier string
 * @i: pointer to current format string index
 *
 * Return: flag:
 */
int get_flag(const char *format, int *i)
{
	int curr_idx, j;
	int flag = 0;
	const char FLAG_CHARS[] = {'-', '+', '0', '#', ' '};
	const int FLAG_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (curr_idx = *i + 1; format[curr_idx]; curr_idx++)
	{
		for (j = 0; FLAG_CHARS[j]; j++)
			if (format[curr_idx] == FLAG_CHARS[j])
			{
				/* bitwise OR assignment */
				flag |= FLAG_ARR[j];
				break;
			}

		if (FLAG_CHARS[j] == 0)
			break;
	}

	*i = curr_idx - 1;

	return (flag);
}
