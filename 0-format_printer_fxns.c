#include "main.h"

/**
 * print_char - prints a character
 *
 * @ap: variable arg pointer
 * @buffer: pointer to  the buffer
 * @flag:  calculated flag.
 * @width: calculated width.
 * @precision: calculated precision
 * @length_mod: calculated length modifier
 *
 * Return: number of bytes printed
 */
int print_char(va_list ap, char *buffer,
	int flag, int width, int precision, int length_mod)
{
	char c = va_arg(ap, int);

	return (handle_char(c, buffer, flag, width, precision, length_mod));
}

/**
 * print_str - prints a string
 *
 * @ap: variable arg pointer
 * @buffer: pointer to buffer
 * @flag:  calculated flag.
 * @width: calculated width.
 * @precision: calculated precision
 * @length_mod: calculated length modifier
 *
 * Return: number of bytes printed
 */
int print_str(va_list ap, char *buffer,
	int flag, int width, int precision, int length_mod)
{
	int len = 0, i;
	char *str = va_arg(ap, char *);

	IGNORE(buffer);
	IGNORE(flag);
	IGNORE(width);
	IGNORE(precision);
	IGNORE(length_mod);
	if (!str)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (str[len])
		len++;

	if (precision >= 0 && precision < len)
		len = precision;

	if (width > len)
	{
		if (flag & F_MINUS)
		{
			write(1, &str[0], len);
			for (i = width - len; i > 0; i--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (i = width - len; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], len);
			return (width);
		}
	}

	return (write(1, str, len));
}

/**
 * print_percent - prints the percentage character
 *
 * @ap: variable arg pointer
 * @buffer: pointer to buffer
 * @flag:  calculated flag.
 * @width: calculated width.
 * @precision: calculated precision
 * @length_mod: calculated length modifier
 *
 * Return: number of bytes printed
 */
int print_percent(va_list ap, char *buffer,
	int flag, int width, int precision, int length_mod)
{
	IGNORE(ap);
	IGNORE(buffer);
	IGNORE(flag);
	IGNORE(width);
	IGNORE(precision);
	IGNORE(length_mod);

	return (write(1, "%%", 1));
}

/**
 * print_int - prints an integer
 *
 * @ap: variable arg pointer
 * @buffer: pointer to buffer
 * @flag:  calculated flag.
 * @width: calculated width.
 * @precision: calculated precision
 * @length_mod: calculated length modifier
 *
 * Return: number of bytes printed
 */
int print_int(va_list ap, char *buffer,
	int flag, int width, int precision, int length_mod)
{
	int i = BUFFER_SIZE - 2;
	int is_neg = 0;
	long int n = va_arg(ap, long int);
	unsigned long int num;

	n = convert_size_mode(n, length_mod);

	if (n == 0)
		buffer[i--] = '0';

	buffer[BUFFER_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_neg = 1;
	}

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (handle_number(is_neg, i, buffer, flag, width, precision,
				length_mod));
}

/**
 * print_unsigned - Prints an unsigned number
 *
 * @ap: variable arg pointer
 * @buffer: pointer to buffer
 * @flag: calculated flag.
 * @width: calculated width.
 * @precision: calculated precision
 * @length_mod: calculated length modifier
 *
 * Return: number of bytes printed
 */
int print_unsigned(va_list ap, char *buffer,
	int flag, int width, int precision, int length_mod)
{
	int i = BUFFER_SIZE - 2;
	unsigned long int num = va_arg(ap, unsigned long int);

	num = convert_size_unsgnd(num, length_mod);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFFER_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (handle_unsgnd(0, i, buffer, flag, width, precision,
				length_mod));
}
