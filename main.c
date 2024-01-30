#include "header.h"
#include "output.c"

// https://web.archive.org/web/20190327023254/http://www.infradead.org/~mchehab/kernel_docs_pdf/linux-input.pdf
// https://web.archive.org/web/20160430145509/http://thiemonge.org/getting-started-with-uinput


int main (int argc, char **argv) {
	int fd_i, fd_o;
	struct input_event data;

	char buf[sizeof(struct input_event)];

	fd_i = open("/dev/input/event0", O_RDONLY);
	fd_o = open("/dev/uinput", O_WRONLY | O_NONBLOCK);
	if (fd_i < 0) {
        printf("Input could not be opened.");
        return 0;
    }
	if (fd_o < 0) {
        printf("Output (uinput) could not be opened. Are you root?");
        return 0;
    }

	createVirtualInput(fd_o);

	while (1) {
		read(fd_i, &data, sizeof(struct input_event));
		printf("Event read. type:%d code:%d value:%d\n", data.type, data.code, data.value);

	}

	getchar();

	//multiple keys can be sent with just one report for press and release each
   	/*emit(fd_o, EV_KEY, KEY_LEFTSHIFT, 1);
	emit(fd_o, EV_KEY, KEY_M, 1);
	emit(fd_o, EV_SYN, SYN_REPORT, 0);
   	emit(fd_o, EV_KEY, KEY_M, 0);
    emit(fd_o, EV_KEY, KEY_LEFTSHIFT, 0);
   	emit(fd_o, EV_SYN, SYN_REPORT, 0);*/
	//read(fd, &data, sizeof(data));
	//printf("%s", data.value);

	/*int sendData[2] = {KEY_LEFTSHIFT, KEY_M};
	printf("Sending chars: %d and %d\n", sendData[0], sendData[1]);
	sendChars(fd_o, sendData, 2);

	getchar();

	sendData[0] = KEY_M;
	printf("Sending chars: %d\n", sendData[0]);
	sendChars(fd_o, sendData, 1);*/

	getchar();



	close(fd_i);
	ioctl(fd_o, UI_DEV_DESTROY);
	close(fd_o);
	return 0;
}
