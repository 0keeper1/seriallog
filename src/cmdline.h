#pragma once

struct CommandLine
{
    bool version;
    bool help;
    unsigned char mode;
    int baudrate;
    int buffersize;
    const char *serialport;
    const char *filepath;
};

void parseCmdLine(int argc, const char *const argv[], struct CommandLine *const cmdline);
