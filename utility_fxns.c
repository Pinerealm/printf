#include "main.h"

/**
 * is_digit - checks if a char is a digit
 * @c: char to be evaluated
 *
 * Return: 1 if digit, 0 otherwise
 */
int is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);

	return (0);
}

/**
 * convert_size_mode - casts a number to the specified integer mode
 *
 * @num: number to be casted.
 * @length_mod: number indicating type to be casted to.
 *
 * Return: casted value of num
 */
long int convert_size_mode(long int num, int length_mod)
{
	if (length_mod == LONG_SPEC)
		return (num);
	else if (length_mod == SHORT_SPEC)
		return ((short)num);

	return ((int)num);
}

/**
 * convert_size_unsgnd - Casts a number to the specified unsigned integer mode
 *
 * @num: Number to be casted
 * @length_mod: Number indicating the type to be casted
 *
 * Return: Casted value of num
 */
long int convert_size_unsgnd(unsigned long int num, int length_mod)
{
	if (length_mod == LONG_SPEC)
		return (num);
	else if (length_mod == SHORT_SPEC)
		return ((unsigned short)num);

	return ((unsigned int)num);
}
