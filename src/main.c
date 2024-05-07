#include <stdio.h>
#include <string.h>
#include "../lib/libserial/libserial.h"

#define VERSION "0.0.0"

#define HELP "Usage: seriallog SERIALPORT BAUDRATE\n\nGithub: https://github.com/0keeper1/seriallog/"

int main(int argc, char *argv[])
{
    int fd;
    int baudrate;
    char buffer[1024];

    if (argc < 2)
    {
        return EXIT_FAILURE;
    }
    else if (argc < 3)
    {
        if (argv[1][0] == '-')
        {
            if (strncmp(argv[1], "-v", 2) == 0 || strncmp(argv[1], "--version", 9) == 0)
            {
                puts(VERSION);
                return EXIT_SUCCESS;
            }
            else if (strncmp(argv[1], "-h", 2) == 0 || strncmp(argv[1], "--help", 9) == 0)
            {
                puts(HELP);
                return EXIT_SUCCESS;
            }
            else
            {
                puts("Error: Invalid Flag.");
                return EXIT_FAILURE;
            }
        }
        puts("Error: Baud Rate required.");
        return EXIT_FAILURE;
    }
    else if (validateSerialPort(argv[1]) < 0)
    {
        puts("Error: Invalid Serial Port.");
        return EXIT_FAILURE;
    }
    else if (validateBaudRate(argv[2]) < 0)
    {
        puts("Error: Invalid Baud Rate.");
        return EXIT_FAILURE;
    }
    baudrate = atoi(argv[2]);

    if ((fd = openSerialPort(argv[1], baudrate, READONLY)) < 0)
    {
        puts("Error: Failed to open Serial Port.");
        return EXIT_FAILURE;
    }

    while (readSerialPort(fd, buffer, 1024) != -1)
    {
        printf("%s", buffer);
    }
    
    if (closeSerialPort(fd) < 0)
    {
        puts("Error: Failed to close Serial Port.");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
