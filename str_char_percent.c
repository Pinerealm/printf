#include "main.h"

/**
 * print_string- Function that prints a string
 * Description: This function prints
 *@ap: list of variable arguments
 * Return: number of character in a string
 *
 */

int print_string(va_list ap)
{
int i;
char *point;
point = (va_arg(ap, char*));

if (point == 0)
{
_putchar('\n');
}

for (i = 0; point[i] != '\0'; i++)
{
_putchar(point[i]);
}
return (i);
}

/**
 * print_char- Function that prints a character
 * Description: This function prints
 *
 *@ap: varaiable parameter
 * Return: number of character
 *
 */

int print_char(va_list ap)
{

char c;
c = (va_arg(ap, int));

_putchar (c);
return (1);

}


/**
 * print_percent- Function that prints a character
 * Description: This function prints
 *
 * Return: number of character
 *
 */

int print_percent(void)
{
_putchar('%');
return (1);
}
