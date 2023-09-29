#include "main.h"

/**
 * get_bit - returns the value of a bit at a given index in a decimal number
 * @n: decimal number
 * @index: index of the bit to retrieve
 *
 * Return: value of the bit at the index, or -1 if an error occurs
 */
int get_bit(unsigned long int n, unsigned int index)
{
	if (index > 63)
		return (-1);

	return ((n >> index) & 1);
}
