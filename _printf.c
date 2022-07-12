#include <stdlib.h>
#include <stdarg.h>
#include "main.h"

/**
 * _printf - custom-made printf implementation
 *
 * @format: format specifier char
 * @...: optional arguments
 *
 * Return: number of bytes written
 */

int _printf(const char *format, ...)
{
	unsigned int b_cnt = 0, i = 0;
	va_list ap;

	if (!format || (format[i] == '%' && !format[i + 1]))
		return (-1);
	if (!format[i])
		return (0);
	va_start(ap, format);

	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			i++;

			b_cnt += char_num_handler(format[i], ap);

		}
		else
		{
			_putchar(format[i]);
			b_cnt++;
		}
		i++;
	}
	va_end(ap);
	return (b_cnt);
}
