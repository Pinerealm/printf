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
 * write_string_len - writes a string up to len characters (buffered)
 * @str: string to write
 * @len: number of characters to write
 * @count: pointer to printed characters count
 *
 * Return: 0 on success, -1 on failure
 */
int write_string_len(const char *str, int len, int *count)
{
	int i = 0, copy_len;

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
 * write_num_full - writes a number with full formatting
 * @num: number to write
 * @flags: active flags
 * @base: base of the number
 * @uppercase: non-zero for uppercase digits
 * @count: pointer to printed characters count
 *
 * Return: 0 on success, -1 on failure
 */
int write_num_full(unsigned long int num, flags_t *flags, int base,
		int uppercase, int *count)
{
	int len, padding, zeros = 0;

	if (num == 0 && flags->precision == 0)
		len = 0;
	else
		len = get_num_len(num, base);

	if (flags->precision > len)
		zeros = flags->precision - len;

	if (flags->hash && num != 0)
		len += (base == 8 && !zeros) ? 1 : (base == 16 ? 2 : 0);

	padding = flags->width - (len + zeros);
	if (write_padding(padding, count) == -1)
		return (-1);

	if (flags->hash && num != 0)
	{
		if (base == 8 && !zeros && write_char('0', count) == -1)
			return (-1);
		if (base == 16)
		{
			if (write_char('0', count) == -1 ||
			    write_char(uppercase ? 'X' : 'x', count) == -1)
				return (-1);
		}
	}

	while (zeros > 0)
	{
		if (write_char('0', count) == -1)
			return (-1);
		zeros--;
	}

	if (len > 0 || (flags->hash && num != 0 && base == 8))
		if (!(num == 0 && flags->precision == 0))
			return (write_unsigned_base(num, base, uppercase, count));
	return (0);
}
