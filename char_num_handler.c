#include "main.h"

/**
 * char_num_handler - handles basic char, string and digit formats
 *
 * @c: format char
 * @ap: variable argument pointer
 *
 * Return: number of bytes written
 */

int char_num_handler(const char c, va_list ap)
{
	unsigned int cnt = 0, i;
	char *str;

	switch (c)
	{
	case 'c':
		_putchar(va_arg(ap, int));
		cnt++;
		break;
	case 's':
		i = 0;
		str = va_arg(ap, char *);
		while (str[i] != '\0')
		{
			_putchar(str[i]);
			cnt++, i++;
		}
		break;
	case '%':
		_putchar('%');
		cnt++;
		break;
	case 'd':
		cnt += print_number(va_arg(ap, int));
		break;
	case 'i':
		cnt += print_number(va_arg(ap, int));
		break;
	}

	return (cnt);
}
