#include <stdlib.h>
#include <termio.h>
#include <fcntl.h>
#include <asm-generic/termbits-common.h>
#include <unistd.h>

speed_t baudRateToInteger(int baud)
{
    switch (baud)
    {
    case 50:
        return B50;
    case 75:
        return B75;
    case 110:
        return B110;
    case 134:
        return B134;
    case 150:
        return B150;
    case 200:
        return B200;
    case 300:
        return B300;
    case 600:
        return B600;
    case 1200:
        return B1200;
    case 1800:
        return B1800;
    case 2400:
        return B2400;
    case 4800:
        return B4800;
    case 9600:
        return B9600;
    case 19200:
        return B19200;
    case 38400:
        return B38400;
    case 57600:
        return B576000;
    case 76800:
        return B57600;
    case 115200:
        return B115200;
    case 230400:
        return B230400;
    case 460800:
        return B460800;
    case 576000:
        return B576000;
    case 921600:
        return B921600;
    default:
        return -1;
    }
}

int setTermioAttr(int fd, struct termios *const termio)
{
    termio->c_cflag &= ~PARENB;
    termio->c_cflag &= ~CSTOPB;
    termio->c_cflag &= ~CSIZE;
    termio->c_cflag |= CS8;
    termio->c_cflag &= CRTSCTS;
    termio->c_cflag |= CREAD | CLOCAL;

    termio->c_iflag &= ~(IXON | IXOFF | IXANY);
    termio->c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL);
    termio->c_lflag &= ~(ICANON | ECHO | ECHOE | ECHONL | ISIG);

    termio->c_oflag &= ~OPOST;

    termio->c_cc[VMIN] = 50;
    termio->c_cc[VTIME] = 1;

    if (tcsetattr(fd, TCSANOW, &termio) < 0)
    {
        return -1;
    }
    return 0;
}

int openSerialPort(const char *serialport, int baud, int mode)
{
    int fd;
    speed_t baudrange;
    struct termios termio;

    fd = open(serialport, mode, O_NOCTTY);
    if (fd < 0)
    {
        return -1;
    }

    if (tcgetattr(fd, &termio) < 0)
    {
        return -1;
    }

    baudrange = baudRateToInteger(baud);

    cfsetispeed(&termio, baudrange);
    cfsetospeed(&termio, baudrange);

    if (setTermioAttr(fd, &termio) < 0)
    {
        return -1;
    }

    return fd;
}

char *readSerialPort(int fd)
{
    ssize_t readsize;
    static char buffer[1024];

    readsize = read(fd, buffer, 1024);
    if (readsize < 0)
    {
        return NULL;
    }

    buffer[readsize] = '\0';
    return buffer;
}

int writeSerialPort(int fd, char *buffer, size_t length)
{
    ssize_t writesize;
    writesize = write(fd, buffer, length);
    if (writesize < (ssize_t) length)
    {
        return -1;
    }
    return 0;
}

inline int closeSerialPort(int fd)
{
    return close(fd);
}