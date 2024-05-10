#include "../lib/libserial/libserial.h"
#include "cmdline.h"
#include <stdio.h>
#include <string.h>

#define VERSION "0.0.0"

#define HELP                                                                                                                \
    "Usage: seriallog [options] <SERIALPORT> <BAUDRATE>\n OPTIONS:\n  -f | --tofile <PATH>\tWrite stdout into the file\n  " \
    "-r | --read\tOpen serialport in ReadOnly mode\n  -w | --write\tOpen serialport in WriteOnly mode\n  -rw | "            \
    "--readwrie\tOpen serialport in ReadWrite mode\n  -h | --help\tDisplay this page\n  -v | --version\tDisplay the "       \
    "version of this program\nGithub: https://github.com/0keeper1/seriallog/"

int main(int argc, const char *const argv[])
{
    int fd;
    int baudrate;
    short int mode = READONLY;
    char buffer[1024];
    struct CommandLine cmdline;

    parseCmdLine(argc, argv, &cmdline);

    if (cmdline.help)
    {
        puts(HELP);
        return EXIT_SUCCESS;
    }
    else if (cmdline.version)
    {
        puts(VERSION);
        return EXIT_SUCCESS;
    }

    if (validateSerialPort(cmdline.serialport) < 0)
    {
        puts("Error: Invalid Serial Port.");
        return EXIT_FAILURE;
    }

    switch (cmdline.mode)
    {
    case 'w':
        mode = WRITEONLY;
        break;
    case 'r':
        mode = READONLY;
        break;
    case 'a':
        mode = READWRITE;
        break;
    }

    if ((fd = openSerialPort(cmdline.serialport, cmdline.baudrate, mode)) < 0)
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
