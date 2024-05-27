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