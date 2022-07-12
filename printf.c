#include "main.h"
/**
 *_printf- function mimics the Printf function
 *This function prints based on variable arguments and formats
 *@format: specifier
 *
 *Return: an integer
 *
 */
int _printf(const char *format, ...)
{
va_list ap;
unsigned int b_cnt = 0, i = 0, j;
char *str;

if (format == NULL)
exit(98);
va_start(ap, format);

while (format && format[i])
{
if (format[i] == '%')
{
i++;
switch (format[i])
{
case 'c':
_putchar(va_arg(ap, int));
b_cnt++;
break;
case 's':
j = 0;
str = va_arg(ap, char *);
while (str[j] != '\0')
{
_putchar(str[j]);
b_cnt++, j++;
}
break;
case 'd'
}
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
