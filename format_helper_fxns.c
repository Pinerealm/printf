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
