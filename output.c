#include "header.h"

void emit(int fd, int type, int code, int val)
{
   struct input_event ie;

   ie.type = type;
   ie.code = code;
   ie.value = val;
   /* timestamp values below are ignored */
   ie.time.tv_sec = 0;
   ie.time.tv_usec = 0;

   write(fd, &ie, sizeof(ie));
}

void sendChars(int fd, int outStr[3]) {
	for (int i = 0; outStr[i]; i++) {
		emit(fd, EV_KEY, outStr[i], 1);
	}
	emit(fd, EV_SYN, SYN_REPORT, 0);
	for (int i = 0; outStr[i]; i++) {
		emit(fd, EV_KEY, outStr[i], 0);
	}
	emit(fd, EV_SYN, SYN_REPORT, 0);
}

void createVirtualInput(int fd, keyMap **mapArrayPtr, int mapCount) {
	struct uinput_setup usetup;

	ioctl(fd, UI_SET_EVBIT, EV_KEY);
	// must set all usable keys here
	for (int i = 0; i < mapCount; i++) {
		for (int j = 0; j < 3; j++) {
				ioctl(fd, UI_SET_KEYBIT, mapArrayPtr[i]->result[j]);
		}
	}

	memset(&usetup, 0, sizeof(usetup));
	usetup.id.bustype = BUS_USB;
	usetup.id.vendor = 0xDEAD; /* sample vendor */
	usetup.id.product = 0xBEEF; /* sample product */
	strcpy(usetup.name, "Cheesecake");

	ioctl(fd, UI_DEV_SETUP, &usetup);
	ioctl(fd, UI_DEV_CREATE);
}