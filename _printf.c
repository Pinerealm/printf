#include "main.h"
/**
 * _printf - custom-made printf implementation
 *@format: format specifier char
 * @...: optional arguments
 *Return: number of bytes written
 */
int _printf(const char *format, ...)
{
	va_list vl;
	int i = 0, j = 0;
	char buff[100] = {0}, tmp[20];
	char *str_arg;

	va_start(vl, format);
	while (format && format[i])
	{
		if (format[i] == '%')
		{
			i++;
			switch (format[i])
			{
			case '%':
			buff[j] = '%', j++;
			break;
			case 'c':
			buff[j] = (char)va_arg(vl, int), j++;
			break;
			case 'd':
			case 'i':
			_itoa(va_arg(vl, int), tmp, 10), strcpy(&buff[j], tmp);
			j += strlen(tmp);
			break;
			case 's':
			str_arg = va_arg(vl, char *), strcpy(&buff[j], str_arg);
			j += strlen(str_arg);
			break;
			}
		}
		else
		{
			buff[j] = format[i];
			j++;
		}
		i++;
	}
	write(1, buff, j), va_end(vl);
	return (j);
}
