#include "main.h"

/**
 * handle_binary - writes an unsigned int in binary form
 * @args: variadic list
 * @flags: active flags
 * @count: pointer to printed characters count
 *
 * Return: 0 on success, -1 on failure
 */
int handle_binary(va_list args, flags_t *flags, int *count)
{
	unsigned int num = va_arg(args, unsigned int);

	(void)flags;
	return (write_unsigned_base((unsigned long int)num, 2, 0, count));
}

/**
 * handle_unsigned - writes an unsigned decimal integer
 * @args: variadic list
 * @flags: active flags
 * @count: pointer to printed characters count
 *
 * Return: 0 on success, -1 on failure
 */
int handle_unsigned(va_list args, flags_t *flags, int *count)
{
	unsigned long int num;

	if (flags->long_num)
		num = va_arg(args, unsigned long int);
	else if (flags->short_num)
		num = (unsigned short)va_arg(args, unsigned int);
	else
		num = va_arg(args, unsigned int);

	return (write_num_full(num, flags, 10, 0, count));
}

/**
 * handle_octal - writes an unsigned integer in octal form
 * @args: variadic list
 * @flags: active flags
 * @count: pointer to printed characters count
 *
 * Return: 0 on success, -1 on failure
 */
int handle_octal(va_list args, flags_t *flags, int *count)
{
	unsigned long int num;

	if (flags->long_num)
		num = va_arg(args, unsigned long int);
	else if (flags->short_num)
		num = (unsigned short)va_arg(args, unsigned int);
	else
		num = va_arg(args, unsigned int);

	return (write_num_full(num, flags, 8, 0, count));
}

/**
 * handle_hex_lower - writes an unsigned integer in lowercase hex
 * @args: variadic list
 * @flags: active flags
 * @count: pointer to printed characters count
 *
 * Return: 0 on success, -1 on failure
 */
int handle_hex_lower(va_list args, flags_t *flags, int *count)
{
	unsigned long int num;

	if (flags->long_num)
		num = va_arg(args, unsigned long int);
	else if (flags->short_num)
		num = (unsigned short)va_arg(args, unsigned int);
	else
		num = va_arg(args, unsigned int);

	return (write_num_full(num, flags, 16, 0, count));
}

/**
 * handle_hex_upper - writes an unsigned integer in uppercase hex
 * @args: variadic list
 * @flags: active flags
 * @count: pointer to printed characters count
 *
 * Return: 0 on success, -1 on failure
 */
int handle_hex_upper(va_list args, flags_t *flags, int *count)
{
	unsigned long int num;

	if (flags->long_num)
		num = va_arg(args, unsigned long int);
	else if (flags->short_num)
		num = (unsigned short)va_arg(args, unsigned int);
	else
		num = va_arg(args, unsigned int);

	return (write_num_full(num, flags, 16, 1, count));
}
