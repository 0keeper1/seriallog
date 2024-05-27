#pragma once

struct CommandLine
{
    bool version;
    bool help;
    bool tofile;
    unsigned char mode;
    int baudrate;
    const char *serialport;
    const char *filepath;
};

void parseCmdLine(int argc, const char *const argv[], struct CommandLine *const cmdline);
