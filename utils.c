#include "main.h"

static char buffer[BUFFER_SIZE];
static int buffer_pos;

/**
 * flush_buffer - writes the buffer to stdout
 * @count: pointer to printed characters count
 *
 * Return: 0 on success, -1 on failure
 */
int flush_buffer(int *count)
{
	int written;

	if (buffer_pos == 0)
		return (0);

	written = write(1, buffer, buffer_pos);
	if (written == -1)
		return (-1);

	(*count) += written;
	buffer_pos = 0;
	return (0);
}

/**
 * write_char - writes a single character to stdout (buffered)
 * @c: character to write
 * @count: pointer to printed characters count
 *
 * Return: 0 on success, -1 on failure
 */
int write_char(char c, int *count)
{
	if (buffer_pos >= BUFFER_SIZE)
	{
		if (flush_buffer(count) == -1)
			return (-1);
	}

	buffer[buffer_pos++] = c;
	return (0);
}

/**
 * write_string - writes a string to stdout (buffered)
 * @str: string to write (uses "(null)" when NULL)
 * @count: pointer to printed characters count
 *
 * Return: 0 on success, -1 on failure
 */
int write_string(const char *str, int *count)
{
	int len = 0, i, copy_len;
	const char *null_str = "(null)";

	if (!str)
		str = null_str;

	while (str[len])
		len++;

	i = 0;
	while (i < len)
	{
		/* Calculate how much we can copy to buffer */
		copy_len = BUFFER_SIZE - buffer_pos;
		if (copy_len > len - i)
			copy_len = len - i;

		/* Copy chunk to buffer */
		while (copy_len > 0)
		{
			buffer[buffer_pos++] = str[i++];
			copy_len--;
		}

		/* Flush if buffer is full */
		if (buffer_pos >= BUFFER_SIZE)
		{
			if (flush_buffer(count) == -1)
				return (-1);
		}
	}
	return (0);
}

/**
 * write_number - writes a signed decimal number
 * @num: number to write
 * @count: pointer to printed characters count
 *
 * Return: 0 on success, -1 on failure
 */
int write_number(long num, int *count)
{
	unsigned long int n;

	if (num < 0)
	{
		if (write_char('-', count) == -1)
			return (-1);
		n = (unsigned long int)num;
		n = -n;
	}
	else
	{
		n = (unsigned long int)num;
	}

	return (write_unsigned_base(n, 10, 0, count));
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
