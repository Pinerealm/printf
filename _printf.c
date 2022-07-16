#include "main.h"

/**
 * _printf - print formatted output to stdout
 * @format: format specifier string
 *
 * Return: number of bytes written
 */

int _printf(const char *format, ...)
{
	int fmt_bytes = 0, total_bytes = 0, buff_idx = 0;
	int i, flag, width, precision, length_mod;
	va_list ap;
	char buffer[BUFFER_SIZE];

	if (!format)
		return (-1);

	va_start(ap, format);

	for (i = 0; format && format[i]; i++)
	{
		if (format[i] != '%')
		{
			buffer[buff_idx++] = format[i];
			if (buff_idx == BUFFER_SIZE)
				print_buf(buffer, &buff_idx);
			total_bytes++;
		}
		else
		{
			print_buf(buffer, &buff_idx);
			flag = get_flag(format, &i);
			width = get_width(format, &i, ap);
			precision = get_precision(format, &i, ap);
			length_mod = get_length_mod(format, &i);
			i++;
			fmt_bytes = format_printer(format, &i, ap, buffer,
					flag, width, precision, length_mod);
			if (fmt_bytes == -1)
				return (-1);
			total_bytes += fmt_bytes;
		}
	}
	print_buf(buffer, &buff_idx);
	va_end(ap);

	return (total_bytes);
}
