#include "main.h"

/**
 * handle_binary - writes an unsigned int in binary form
 * @args: variadic list
 * @count: pointer to printed characters count
 *
 * Return: 0 on success, -1 on failure
 */
int handle_binary(va_list args, int *count)
{
	unsigned int num = va_arg(args, unsigned int);

	return (write_unsigned_base((unsigned long int)num, 2, 0, count));
}

/**
 * handle_unsigned - writes an unsigned decimal integer
 * @args: variadic list
 * @count: pointer to printed characters count
 *
 * Return: 0 on success, -1 on failure
 */
int handle_unsigned(va_list args, int *count)
{
	unsigned int num = va_arg(args, unsigned int);

	return (write_unsigned_base((unsigned long int)num, 10, 0, count));
}

/**
 * handle_octal - writes an unsigned integer in octal form
 * @args: variadic list
 * @count: pointer to printed characters count
 *
 * Return: 0 on success, -1 on failure
 */
int handle_octal(va_list args, int *count)
{
	unsigned int num = va_arg(args, unsigned int);

	return (write_unsigned_base((unsigned long int)num, 8, 0, count));
}

/**
 * handle_hex_lower - writes an unsigned integer in lowercase hex
 * @args: variadic list
 * @count: pointer to printed characters count
 *
 * Return: 0 on success, -1 on failure
 */
int handle_hex_lower(va_list args, int *count)
{
	unsigned int num = va_arg(args, unsigned int);

	return (write_unsigned_base((unsigned long int)num, 16, 0, count));
}

/**
 * handle_hex_upper - writes an unsigned integer in uppercase hex
 * @args: variadic list
 * @count: pointer to printed characters count
 *
 * Return: 0 on success, -1 on failure
 */
int handle_hex_upper(va_list args, int *count)
{
	unsigned int num = va_arg(args, unsigned int);

	return (write_unsigned_base((unsigned long int)num, 16, 1, count));
}
