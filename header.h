#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <fcntl.h>
#include <linux/input.h>
#include <linux/uinput.h>
#include <string.h>
#include <unistd.h>


// output.c
void emit(int fd, int type, int code, int val);
void sendChars(int fd, int* str, int count);
void createVirtualInput(int fd);

#endif