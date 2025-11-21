#include "main.h"

/**
 * _printf - custom printf implementation
 * @format: format string
 *
 * Return: number of characters printed or -1 on failure
 */
int _printf(const char *format, ...)
{
	va_list args;
	int count = 0, f_idx = 0;

	if (!format)
		return (-1);

	va_start(args, format);
	while (format[f_idx])
	{
		if (format[f_idx] == '%')
		{
			if (process_specifier(format, &f_idx, args, &count) == -1)
			{
				va_end(args);
				return (-1);
			}
		}
		else if (write_char(format[f_idx], &count) == -1)
		{
			va_end(args);
			return (-1);
		}
		f_idx++;
	}
	if (flush_buffer(&count) == -1)
	{
		va_end(args);
		return (-1);
	}
	va_end(args);
	return (count);
}
