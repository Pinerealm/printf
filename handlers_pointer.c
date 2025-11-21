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
	int len, padding, zeros = 0;
	char pad_char = ' ';

	if (!ptr)
	{
		len = 5; /* Length of "(nil)" */
		padding = flags->width - len;
		if (write_chars(' ', padding, count) == -1)
			return (-1);
		return (write_string_len("(nil)", 5, count));
	}

	addr = (unsigned long int)ptr;
	len = get_num_len(addr, 16);

	if (flags->precision > len)
		zeros = flags->precision - len;

	len += 2; /* For "0x" */

	if (flags->zero && flags->precision == -1)
		pad_char = '0';

	padding = flags->width - (len + zeros);

	if (write_padded(padding, pad_char, "0x", count) == -1)
		return (-1);

	if (write_chars('0', zeros, count) == -1)
		return (-1);

	/* Print address in lowercase hexadecimal */
	return (write_unsigned_base(addr, 16, 0, count));
}
