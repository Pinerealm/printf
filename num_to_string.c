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
		convert(va_arg(vl, int), tmp, 10);
		strcpy(&buff[j], tmp);
		j += strlen(tmp);
		break;
	/* Convert decimal */
	case 'i':
		convert(va_arg(vl, int), tmp, 10);
		strcpy(&buff[j], tmp);
		j += strlen(tmp);
		break;
	/* Convert hex */
	case 'x':
		convert(va_arg(vl, int), tmp, 16);
		strcpy(&buff[j], tmp);
		j += strlen(tmp);
		break;
	/* Convert octal */
	case 'o':
		convert(va_arg(vl, int), tmp, 8);
		strcpy(&buff[j], tmp);
		j += strlen(tmp);
		break;
	}

	return (j);
}

