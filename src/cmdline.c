#include "cmdline.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

bool checkFlag(const char *const argument, const char *const smallflag, const char *const largeflag)
{
    return strncmp(argument, smallflag, strlen(smallflag)) == 0 || strncmp(argument, largeflag, strlen(largeflag)) == 0;
}

bool isFlag(const char *const argument)
{
    return argument[0] == '-' || (argument[0] == '-' && argument[1] == '-');
}

void parseCmdLine(int argc, const char *const argv[], struct CommandLine *const cmdline)
{
    unsigned char pervflag = ' ';
    cmdline->help = false;
    cmdline->version = false;
    cmdline->tofile = false;
    cmdline->mode = 'r';

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
            else if (checkFlag(argv[loopc], "-m", "--mode"))
            {
                pervflag = 'm';
                continue;
            }
            else if (checkFlag(argv[loopc], "-f", "--tofile"))
            {
                cmdline->tofile = true;
                cmdline->filepath = isFlag(argv[argc > (loopc + 1) ? (loopc++) : loopc]) ? getcwd(NULL, 0) : argv[loopc];
            }
            pervflag = ' ';
        }
        else
        {
            if (pervflag == 'm')
            {
                if (strncmp(argv[loopc], "r", 2) == 0)
                {
                    cmdline->mode = 'r';
                }
                else if (strncmp(argv[loopc], "w", 2) == 0)
                {
                    cmdline->mode = 'w';
                }
                else if (strncmp(argv[loopc], "rw", 3) == 0)
                {
                    cmdline->mode = 'a';
                }
            }
            else if (argc - 1 == loopc)
            {
                cmdline->baudrate = atoi(argv[loopc]);
            }
            else
            {
                cmdline->serialport = argv[loopc];
            }
            pervflag = ' ';
        }
    }
}