#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <linux/input.h>
#include <linux/uinput.h>
#include <string.h>
#include <unistd.h>

typedef struct {
	int eventType;
	int eventCode;
	int eventValue;
	int result[3];
} keyMap;

// maps.c
int loadKeymap(keyMap **mapsArrayPtr, char *filename);

// output.c
void emit(int fd, int type, int code, int val);
void sendChars(int fd, int* str, int count);
void createVirtualInput(int fd);

#endif