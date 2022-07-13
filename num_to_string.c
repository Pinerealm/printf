#include "main.h"

/**
* num_to_string - converts an integer to a string
* @vl: variable arg pointer
* @c: The number format
*
* Return: no of bytes printed
*/

int num_to_string(va_list vl, const char c)
{
	int j = 0;
	char buff[100] = {0}, tmp[20];

	switch (c)
	{
	/* Convert decimal */
	case 'd':
		_itoa(va_arg(vl, int), tmp, 10);
		strcpy(&buff[j], tmp);
		j += strlen(tmp);
		break;
	/* Convert decimal */
	case 'i':
		_itoa(va_arg(vl, int), tmp, 10);
		strcpy(&buff[j], tmp);
		j += strlen(tmp);
		break;
	/* Convert hex */
	case 'x':
		_itoa(va_arg(vl, int), tmp, 16);
		strcpy(&buff[j], tmp);
		j += strlen(tmp);
		break;
	/* Convert octal */
	case 'o':
		_itoa(va_arg(vl, int), tmp, 8);
		strcpy(&buff[j], tmp);
		j += strlen(tmp);
		break;
	}

	return (j);
}

