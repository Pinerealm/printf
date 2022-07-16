#include "main.h"

/**
 * handle_char - writes a character while handling specs
 *
 * @c: character to write
 * @buffer: pointer to buffer
 * @flag:  calculated flag.
 * @width: calculated width.
 * @precision: calculated precision
 * @length_mod: calculated length modifier
 *
 * Return: number of bytes printed
 */
int handle_char(char c, char *buffer,
	int flag, int width, int precision, int length_mod)
{
	int i = 0;
	char pad = ' ';

	IGNORE(precision);
	IGNORE(length_mod);

	if (flag & F_ZERO)
		pad = '0';

	buffer[i++] = c;
	buffer[i] = '\0';

	if (width > 1)
	{
		buffer[BUFFER_SIZE - 1] = '\0';
		for (i = 0; i < width - 1; i++)
			buffer[BUFFER_SIZE - i - 2] = pad;

		if (flag & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFFER_SIZE - i - 1], width - 1));
		else
			return (write(1, &buffer[BUFFER_SIZE - i - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

/**
 * handle_number - writes a number as a string while handling specs
 *
 * @is_neg: 1 if number is negative, 0 otherwise
 * @idx: buffer index to start from
 * @buffer: pointer to buffer
 * @flag:  calculated flag
 * @width: calculated width
 * @precision: calculated precision
 * @length_mod: calculated length modifier
 *
 * Return: number of bytes printed
 */
int handle_number(int is_neg, int idx, char *buffer,
	int flag, int width, int precision, int length_mod)
{
	int len = BUFFER_SIZE - idx - 1;
	char pad = ' ', extra_ch = 0;

	IGNORE(length_mod);

	if ((flag & F_ZERO) && !(flag & F_MINUS))
		pad = '0';
	if (is_neg)
		extra_ch = '-';
	else if (flag & F_PLUS)
		extra_ch = '+';
	else if (flag & F_SPACE)
		extra_ch = ' ';

	return (write_number(idx, buffer, flag, width, precision,
		len, pad, extra_ch));
}

/**
 * write_number - writes a number to the stdout as a string
 *
 * @idx: buffer index to start writing from
 * @buffer: pointer to the buffer
 * @flag: calculated flag
 * @width: calculated width
 * @precision: calculated precision
 * @len: number length
 * @pad: character to pad with
 * @extra_ch: extra needed character
 *
 * Return: number of bytes written
 */
int write_number(int idx, char *buffer, int flag, int width, int precision,
		int len, char pad, char extra_ch)
{
	int i, pad_start = 1;

	if (!precision && idx == BUFFER_SIZE - 2 && buffer[idx] == '0'
		&& !width)
		return (0);
	if (!precision && idx == BUFFER_SIZE - 2 && buffer[idx] == '0')
		buffer[idx] = pad = ' ';
	if (precision > 0 && precision < len)
		pad = ' ';
	while (precision > len)
		buffer[--idx] = '0', len++;
	if (extra_ch != 0)
		len++;
	if (width > len)
	{
		for (i = 1; i < width - len + 1; i++)
			buffer[i] = pad;
		buffer[i] = '\0';
		if (flag & F_MINUS && pad == ' ')
		{
			if (extra_ch)
				buffer[--idx] = extra_ch;
			return (write(1, &buffer[idx], len) + write(1, &buffer[1], i - 1));
		}
		else if (!(flag & F_MINUS) && pad == ' ')
		{
			if (extra_ch)
				buffer[--idx] = extra_ch;
			return (write(1, &buffer[1], i - 1) + write(1, &buffer[idx], len));
		}
		else if (!(flag & F_MINUS) && pad == '0')
		{
			if (extra_ch)
				buffer[--pad_start] = extra_ch;
			return (write(1, &buffer[pad_start], i - pad_start) +
				write(1, &buffer[idx], len - (1 - pad_start)));
		}
	}
	if (extra_ch)
		buffer[--idx] = extra_ch;
	return (write(1, &buffer[idx], len));
}

/**
 * handle_unsgnd - writes an unsigned number as a string while handling specs
 *
 * @is_neg: flag indicating if number is negative
 * @idx: buffer index to start from
 * @buffer: pointer to buffer
 * @flag:  calculated flag
 * @width: calculated width
 * @precision: calculated precision
 * @length_mod: calculated length modifier
 *
 * Return: number of bytes printed
 */
int handle_unsgnd(int is_neg, int idx, char *buffer,
	int flag, int width, int precision, int length_mod)
{
	int len = BUFF_SIZE - ind - 1, i = 0;
	char pad = ' ';

	IGNORE(is_neg);
	IGNORE(length_mod);

	if (precision == 0 && idx == BUFFER_SIZE - 2 && buffer[idx] == '0')
		return (0);

	if (precision > 0 && precision < len)
		pad = ' ';

	while (precision > len)
	{
		buffer[--idx] = '0';
		len++;
	}

	if ((flag & F_ZERO) && !(flag & F_MINUS))
		pad = '0';

	if (width > len)
	{
		for (i = 0; i < width - len; i++)
			buffer[i] = pad;

		buffer[i] = '\0';

		if (flag & F_MINUS)
		{
			return (write(1, &buffer[idx], len) + write(1, &buffer[0], i));
		}
		else
		{
			return (write(1, &buffer[0], i) + write(1, &buffer[idx], len));
		}
	}

	return (write(1, &buffer[idx], len));
}
