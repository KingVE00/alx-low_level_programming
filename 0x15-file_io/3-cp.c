#include "main.h"
#include <stdio.h>
#include <stdlib.h>

char *allocate_buffer(char *destination_file);
void close_descriptor(int descriptor);

/**
 * allocate_buffer - Allocates a 1024-byte buffer.
 * @destination_file: The name of the file to store characters for.
 *
 * Return: A pointer to the newly allocated buffer.
 */
char *allocate_buffer(char *destination_file)
{
    char *file_buffer;

    file_buffer = malloc(sizeof(char) * 1024);

    if (file_buffer == NULL)
    {
        dprintf(STDERR_FILENO,
                "Error: Can't write to %s\n", destination_file);
        exit(99);
    }

    return (file_buffer);
}

/**
 * close_descriptor - Closes a file descriptor.
 * @descriptor: The file descriptor to be closed.
 */
void close_descriptor(int descriptor)
{
    int close_status;

    close_status = close(descriptor);

    if (close_status == -1)
    {
        dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", descriptor);
        exit(100);
    }
}

/**
 * main - Copies the contents of one file to another.
 * @argc: The number of arguments supplied to the program.
 * @argv: An array of pointers to the arguments.
 *
 * Return: 0 on success.
 *
 * Description: If the argument count is incorrect, exit with code 97.
 * If the source file does not exist or cannot be read, exit with code 98.
 * If the destination file cannot be created or written to, exit with code 99.
 * If either file cannot be closed, exit with code 100.
 */
int main(int argc, char *argv[])
{
    int source_file_descriptor, destination_file_descriptor, read_status, write_status;
    char *copy_buffer;

    if (argc != 3)
    {
        dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
        exit(97);
    }

    copy_buffer = allocate_buffer(argv[2]);
    source_file_descriptor = open(argv[1], O_RDONLY);
    read_status = read(source_file_descriptor, copy_buffer, 1024);
    destination_file_descriptor = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0664);

    do
    {
        if (source_file_descriptor == -1 || read_status == -1)
        {
            dprintf(STDERR_FILENO,
                    "Error: Can't read from file %s\n", argv[1]);
            free(copy_buffer);
            exit(98);
        }

        write_status = write(destination_file_descriptor, copy_buffer, read_status);
        if (destination_file_descriptor == -1 || write_status == -1)
        {
            dprintf(STDERR_FILENO,
                    "Error: Can't write to %s\n", argv[2]);
            free(copy_buffer);
            exit(99);
        }

        read_status = read(source_file_descriptor, copy_buffer, 1024);
        destination_file_descriptor = open(argv[2], O_WRONLY | O_APPEND);

    } while (read_status > 0);

    free(copy_buffer);
    close_descriptor(source_file_descriptor);
    close_descriptor(destination_file_descriptor);

    return (0);
}
