#include "main.h"

/**
 * handle_pointer - writes a pointer address in hexadecimal format
 * @args: variadic list
 * @flags: active flags
 * @count: pointer to printed characters count
 *
 * Return: 0 on success, -1 on failure
 */
int handle_pointer(va_list args, flags_t *flags, int *count)
{
	void *ptr = va_arg(args, void *);
	unsigned long int addr;
	int len, padding;

	if (!ptr)
	{
		len = 5; /* Length of "(nil)" */
		padding = flags->width - len;
		if (flags->minus)
		{
			if (write_string_len("(nil)", 5, count) == -1)
				return (-1);
			return (write_chars(' ', padding, count));
		}
		if (write_chars(' ', padding, count) == -1)
			return (-1);
		return (write_string_len("(nil)", 5, count));
	}

	addr = (unsigned long int)ptr;

	return (write_number(addr, flags, 16, "0x", 0, count));
}
