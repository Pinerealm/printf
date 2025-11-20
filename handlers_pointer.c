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

	(void)flags;
	if (!ptr)
		return (write_string("(nil)", count));

	addr = (unsigned long int)ptr;

	/* Print "0x" prefix */
	if (write_char('0', count) == -1)
		return (-1);
	if (write_char('x', count) == -1)
		return (-1);

	/* Print address in lowercase hexadecimal */
	return (write_unsigned_base(addr, 16, 0, count));
}
