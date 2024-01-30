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

void sendChars(int fd, int* str, int count) {
	for (int i = 0; i < count; i++) {
		emit(fd, EV_KEY, str[i], 1);
	}
	emit(fd, EV_SYN, SYN_REPORT, 0);
	for (int i = 0; i < count; i++) {
		emit(fd, EV_KEY, str[i], 0);
	}
	emit(fd, EV_SYN, SYN_REPORT, 0);
}

void createVirtualInput(int fd) {
	struct uinput_setup usetup;

	ioctl(fd, UI_SET_EVBIT, EV_KEY);
	//must set all usable keys here
	ioctl(fd, UI_SET_KEYBIT, KEY_LEFTSHIFT);
	ioctl(fd, UI_SET_KEYBIT, KEY_M);

	memset(&usetup, 0, sizeof(usetup));
	usetup.id.bustype = BUS_USB;
	usetup.id.vendor = 0xDEAD; /* sample vendor */
	usetup.id.product = 0xBEEF; /* sample product */
	strcpy(usetup.name, "uinput virtual device");

	ioctl(fd, UI_DEV_SETUP, &usetup);
	ioctl(fd, UI_DEV_CREATE);

}