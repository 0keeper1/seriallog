#ifndef CMD_LINE
#define CMD_LINE

struct CommandLine
{
    bool version;
    bool help;
    bool tofile;
    unsigned char mode;
    int baudrate;
    char *serialport;
    char *filepath;
};

void parseCmdLine(int argc, const char *const argv[], struct CommandLine *const cmdline);

#endif