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
void printKeyMap(keyMap **mapsArrayPtr, int mapCount);
void matchInput(int fd, struct input_event input, keyMap **mapsArrayPtr, int mapCount);

// output.c
void emit(int fd, int type, int code, int val);
void sendChars(int fd, int outStr[3], int value);
void createVirtualInput(int fd, keyMap **mapsArrayPtr, int mapCount);

#endif