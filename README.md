
# Serial Log

A Lightweight And Simple Serial Port Logger.

## Installation

Manual:

```bash
  make
  ./build/seriallog -h
```

## Usage

```
Usage: seriallog [options] <SERIALPORT> <BAUDRATE>
 OPTIONS:
  -f | --tofile <PATH>  Write stdout into the file
  -m | --mode <MODE>    Open serialport mode (r = ReadOnly, w = WriteOnly, rw = ReadWrite)
  -h | --help   Display this page
  -v | --version        Display the version of this program
  -b | --buffersize <SIZE>      Buffer size to hold the string data (default: 1024)
```

```bash
seriallog -b 2042 -m r /dev/ttyUSB0 9600
```
