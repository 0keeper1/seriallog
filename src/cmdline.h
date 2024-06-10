#pragma once

struct CommandLine
{
    bool version;
    bool help;
    unsigned char mode;
    int baudrate;
    int buffersize;
    char *serialport;
    char *filepath;
};

void parseCmdLine(int argc, char *argv[], struct CommandLine *const cmdline);
