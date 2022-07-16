#include "main.h"

/**
 * format_printer - prints a variable arg according to the given specification
 *
 * @format: format specifier string
 * @ap: variable arg pointer
 * @idx: pointer to the current index in the format string
 * @buffer: pointer to the buffer
 * @flags: calculated flags
 * @width: calculated width
 * @precision: calculated precision
 * @length_mod: calculated length modifier
 *
 * Return: 1 or 2;
 */

int format_printer(const char *format, int *idx, va_list ap, char *buffer,
	int flags, int width, int precision, int length_mod)
{
	int i, added_len = 0, byte_count = -1;
	fmt_spec fmt_lib[] = {
		{'c', print_char}, {'s', print_str}, {'%', print_percent},
		{'i', print_int}, {'d', print_int}, {'\0', NULL}
	};

	for (i = 0; fmt_lib[i].spec; i++)
		if (format[*idx] == fmt_lib[i].spec)
			return (fmt_lib[i].func(ap, buffer, flags, width,
						precision, length_mod));

	if (!fmt_lib[i].spec)
	{
		if (format[*idx] == '\0')
			return (-1);
		added_len += write(1, "%%", 1);
		if (format[*idx - 1] == ' ')
			added_len += write(1, " ", 1);
		else if (width)
		{
			--(*idx);
			while (format[*idx] != ' ' && format[*idx] != '%')
				--(*idx);
			if (format[*idx] == ' ')
				--(*idx);
			return (1);
		}
		added_len += write(1, &format[*idx], 1);
		return (added_len);
	}
	return (byte_count);
}
