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
extern int openSerialPort(const char *serialport, int baud, int mode);

/**
 *  @brief read data from the serial port
 *  @param fd file descriptor
 *  @param buffer pointer to buffer
 *  @param buffercap capacity of buffer
 *  @return the line read from the serial ports
 */
extern int readSerialPort(int fd, char *const buffer, int buffercap);

/** 
 * @brief write buffer to serial port
 * @param fd file descriptor
 * @param buffer string buffer just allow the UTF-8 format
 * @param length lenght of buffer
 * @return [<0] failure [>=0] success
 */
extern int writeSerialPort(int fd, char *buffer, size_t length);


/**
 * @brief validate the serial port is openable and is valid path
 * @param serialport takes the string name of the serial port "/dev/ttyUSB"
 * @return [<0] failure [>=0] success
 */
extern int validateSerialPort(const char *const serialport);

/**
 * @brief validate baud rate string
 * @param baudrate baud rate string
 * @return [<0] failure [>=0] success
 */
extern int validateBaudRate(const char *const baudrate);

/** 
 * @brief close serial port
 * @param fd file descriptor
 * @return [<0] failure [>=0] success
 */ 
extern int closeSerialPort(int fd);

#endif