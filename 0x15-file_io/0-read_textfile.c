#include "main.h"
#include <stdlib.h>

/**
 * read_textfile - Read text file and print to STDOUT.
 * @filename: Text file being read.
 * @letters: Number of letters to be read.
 * Return: Actual number of bytes read and printed; 0 on failure or if filename is NULL.
 */
ssize_t read_textfile(const char *filename, size_t letters)
{
	int fd;
	ssize_t r;
	char *buf;

	if (filename == NULL)
		return (0);

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);

	buf = malloc(letters);
	if (buf == NULL)
	{
		close(fd);
		return (0);
	}

	r = read(fd, buf, letters);
	if (r == -1)
	{
		close(fd);
		free(buf);
		return (0);
	}

	write(STDOUT_FILENO, buf, r);

	close(fd);
	free(buf);

	return (r);
}
