#include "../lib/libserial/libserial.h"
#include <stdio.h>

int printToStdOut(int fd, int buffersize)
{
    char buffer[buffersize];

    while (readSerialPort(fd, buffer, buffersize) != -1)
    {
        printf("%s", buffer);
    }

    return 0;
}

int printToFile(int fd, const char *const filepath, int buffersize)
{
    char buffer[buffersize];

    FILE *fileptr;

    if ((fileptr = fopen(filepath, "a")) == NULL)
    {
        return -1;
    }

    while (readSerialPort(fd, buffer, buffersize) != -1)
    {
        fputs(buffer, fileptr);
    }

    fclose(fileptr);

    return 0;
}