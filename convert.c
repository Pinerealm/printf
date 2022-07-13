#include "main.h"
/**
 * _printf - custom-made printf implementation
 *@format: format specifier char
 * @...: optional arguments
 *Return: number of bytes written
 */

void swap(char *x, char *y)
{
    char t = *x;
    *x = *y;
    *y = t;
}
/**
 * reverse- custom-made printf implementation
 *@buffer: format specifier char
 * @i: optional arguments
 * @j: optional arguments
 *Return: number of bytes written
 */
char *reverse(char *buffer, int i, int j)
{
    while (i < j)
    {
        swap(&buffer[i++], &buffer[j--]);
    }

    return buffer;
}

/**
 * convert - custom-made printf implementation
 *@value: format specifier char
 * @buffer: optional arguments
 * @base: optional arguments
 *Return: number of bytes written
 */
char *convert(int value, char *buffer, int base)
{
  int n = abs(value);
  int i;

    if (base < 2 || base > 32)
    {
        return buffer;
    }

  
     i = 0;
    while (n)
    {
        int r = n % base;

        if (r >= 10)
        {
            buffer[i++] = 65 + (r - 10);
        }
        else
        {
            buffer[i++] = 48 + r;
        }

        n = n / base;
    }

    if (i == 0)
    {
        buffer[i++] = '0';
    }

    if (value < 0 && base == 10)
    {
        buffer[i++] = '-';
    }

    buffer[i] = '\0';
    return reverse(buffer, 0, i - 1);
}
