#include <stdio.h>
#include "../lib/libserial/libserial.h"

const char *HELP_CMD = "Usage: seriallog SERIALPORT BAUDRATE\n\nGithub: https://github.com/0keeper1/seriallog/";

int main(int argc, char *argv[])
{
    int fd;
    int baudrate; 
    char *ptr;

    if (argc < 2)
    {
        puts(HELP_CMD);
        return EXIT_FAILURE;
    }
    else if (argc < 3)
    {
        return EXIT_FAILURE;
    }
    else if (validateSerialPort(argv[1]) < 0)
    {
        return EXIT_FAILURE;
    }
    else if (validateBaudRate(argv[2]) < 0)
    {
        return EXIT_FAILURE;
    }
    baudrate = atoi(argv[2]);

    if ((fd = openSerialPort(argv[1], baudrate, READONLY)) < 0)
    {
        return EXIT_FAILURE;
    }

    do
    {
        ptr = readSerialPort(fd);
        printf("%s", ptr);
    } while (ptr != NULL);
    
    return EXIT_SUCCESS;
}
