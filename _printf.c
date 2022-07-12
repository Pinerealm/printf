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
	int b_cnt = 0, i = 0, cnt = 0;
	va_list ap;

	if (!format)
		return (-1);
	va_start(ap, format);

	while (format[i])
	{
		if (format[i] != '%')
		{
			_putchar(format[i]);
			b_cnt++, i++;
			continue;
		}
		if (format[i + 1] == '%')
		{
			_putchar('%');
			i += 2, b_cnt++;
			continue;
		}
		if (format[i + 1] == '\0')
			return (-1);

		cnt = char_num_handler(format[i + 1], ap);
		b_cnt += cnt;
		i += 2;
	}
	va_end(ap);
	return (b_cnt);
}
