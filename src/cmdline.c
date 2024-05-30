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
    cmdline->help = false;
    cmdline->version = false;
    cmdline->buffersize = 1024;
    cmdline->filepath = NULL;
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
                if (strncmp(argv[loopc + 1], "r", 2) == 0)
                {
                    cmdline->mode = 'r';
                }
                else if (strncmp(argv[loopc + 1], "w", 2) == 0)
                {
                    cmdline->mode = 'w';
                }
                else if (strncmp(argv[loopc + 1], "rw", 3) == 0)
                {
                    cmdline->mode = 'a';
                }
                loopc++;
            }
            else if (checkFlag(argv[loopc], "-b", "--buffersize"))
            {
                cmdline->buffersize = atoi(argv[loopc + 1]);
                loopc++;
            }
            else if (checkFlag(argv[loopc], "-f", "--tofile"))
            {
                cmdline->filepath = argv[loopc + 1];
                loopc++;
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
