 #include "main.h"

/**
 * print_binary - prints the binary equivalent of a decimal number
 * @n: number to print in binary
 */
void print_binary(unsigned long int n)
{
	int i, found_one = 0;

	for (i = 63; i >= 0; i--)
	{
		unsigned long int bit = n >> i & 1;
		if (bit || found_one)
		{
			_putchar(bit ? '1' : '0');
			found_one = 1;
		}
	}
	if (!found_one)
		_putchar('0');
}
