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
unsigned int cnt = 0;

switch (c)
{
case 'c':
print_char(ap);
cnt++;
break;
case 's':
print_string(ap);
cnt++;
break;
case '%':
_putchar('%');
cnt++;
break;
case 'd':
cnt += print_integers(ap);
break;
case 'i':
cnt += print_integers(ap);
break;
}

return (cnt);
}
