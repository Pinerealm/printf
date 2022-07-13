#include "main.h"

/**
* print_number - Prints a number
* @n: The number to print
*
* Return: no of bytes printed
*/

int print_number(int n)
{
	int num = n, cnt = 0;

	if (n)
	{
		if (n < 0)
		{
			_putchar('-');
			cnt++;
			num = -num;
		}
		if (num > 9)
		{
			print_number(num / 10);
			cnt++;
		}
		_putchar(num % 10 + '0');
	}

	return (cnt);
}
