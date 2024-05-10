#include "cmdline.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

bool __attribute__((always_inline))
checkFlag(const char *const argument, const char *const smallflag, const char *const largeflag)
{
    return strncmp(argument, smallflag, strlen(smallflag)) == 0 || strncmp(argument, largeflag, strlen(largeflag)) == 0;
}

bool __attribute__((always_inline)) isFlag(const char *const argument)
{
    return argument[0] == '-' || (argument[0] == '-' && argument[1] == '-');
}

void parseCmdLine(int argc, const char *const argv[], struct CommandLine *const cmdline)
{
    cmdline->help = false;
    cmdline->version = false;
    cmdline->tofile = false;
    for (int loopc = 1; loopc != argc; ++loopc)
    {
        if (isFlag(argv[loopc]))
        {
            if (checkFlag(argv[loopc], "-h", "--help"))
            {
                cmdline->help = true;
            }
            else if (checkFlag(argv[loopc], "-v", "--version"))
            {
                cmdline->version = true;
            }
            else if (checkFlag(argv[loopc], "-w", "--write"))
            {
                cmdline->mode = 'w';
            }
            else if (checkFlag(argv[loopc], "-r", "--read"))
            {
                cmdline->mode = 'r';
            }
            else if (checkFlag(argv[loopc], "-rw", "--readwrite"))
            {
                cmdline->mode = 'a'; // 'a' means read and write
            }
            else if (checkFlag(argv[loopc], "-f", "--tofile"))
            {
                cmdline->tofile = true;
                cmdline->filepath = isFlag(argv[argc > (loopc + 1) ? (loopc++) : loopc]) ? getcwd(NULL, 0) : argv[loopc];
            }
        }
        else
        {
            if (argc - 1 == loopc)
            {
                cmdline->baudrate = atoi(argv[loopc]);
            }
            else
            {
                cmdline->serialport = argv[loopc];
            }
        }
    }
}