#include "main.h"

/**
 * print_buf - prints the buffer's contents
 *
 * @buffer: pointer to the buffer
 * @buff_idx: pointer to current buffer index.
 *
 * Return: void
 */

void print_buf(char *buffer, int *buff_idx)
{
	if (*buff_idx > 0)
		write(1, buffer, *buff_idx);

	*buff_idx = 0;
}
