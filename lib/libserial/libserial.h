#ifndef LIB_SERIAL_PORT
#define LIB_SERIAL_PORT

#include <stdlib.h>

/** 
 * @brief enumerate for openSerialPort mode
 */
typedef enum
{
    READONLY = 00,
    WRITEONLY = 01,
    READWRITE = 02,
} Mode;

/**
 *  @brief open the serial port
 *  @param serialport takes the string name of the serial port "/dev/ttyUSB"
 *  @param baud baud rate
 *  @param mode open the serial port mode (READONLY, WRITEONLY, READ/WRITE)
 *  @return [<0] failure [>=0] success
 */ 
extern int openSerialPort(char *serialport, int baud, int mode);

/**
 *  @brief read data from the serial port
 *  @param fd file descriptor
 *  @return line readed from the serial port
 */
extern char *readSerialPort(int fd);

/** 
 * @brief write buffer to serial port
 * @param fd file descriptor
 * @param buffer string buffer just allow the UTF-8 format
 * @param length lenght of buffer
 * @return [<0] failure [>=0] success
 */
extern int writeSerialPort(int fd, char *buffer, size_t length);

/** 
 * @brief close serial port
 * @param fd file descriptor
 * @return [<0] failure [>=0] success
 */ 
extern inline int closeSerialPort(int fd);

#endif