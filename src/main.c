#include "../lib/libserial/libserial.h"
#include "cmdline.h"
#include "read.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define VERSION "1.0.0"

#define HELP                                                                                                                \
    "Usage: seriallog [options] <SERIALPORT> <BAUDRATE>\n OPTIONS:\n  -f | --tofile <PATH>\tWrite stdout into the file\n  " \
    "-m | --mode <MODE>\tOpen serialport mode (r = ReadOnly, w = WroteOnly, rw = ReadWrite)\n  -h | --help\tDisplay this "  \
    "page\n  "                                                                                                              \
    "-v | --version\tDisplay the "                                                                                          \
    "version of this program\n  -b | --buffersize <SIZE>\tBuffer size to hold the string data (default: 1024)\nGithub: "    \
    "https://github.com/0keeper1/seriallog/"

int main(int argc, const char *const argv[])
{
    int fd;
    short int mode = READONLY;
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

    printToStdOut(fd, cmdline.buffersize);

    if (closeSerialPort(fd) < 0)
    {
        puts("Error: Failed to close Serial Port.");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
