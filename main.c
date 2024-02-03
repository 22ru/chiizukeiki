#include "header.h"

// https://web.archive.org/web/20190327023254/http://www.infradead.org/~mchehab/kernel_docs_pdf/linux-input.pdf
// https://web.archive.org/web/20160430145509/http://thiemonge.org/getting-started-with-uinput


int main (int argc, char **argv) {
	int fd_i, fd_uinput;
	struct input_event eventData;
	int mapCount = 0;

	keyMap *mapsArray[40];

	if (argc > 1) {
		printf("Loading config from file %s\n", argv[1]);
		mapCount = loadKeymap(mapsArray, argv[1]);
	} else {
		mapCount = loadKeymap(mapsArray, "./default.map");
	}

	fd_uinput = open("/dev/uinput", O_WRONLY | O_NONBLOCK);
	if (fd_uinput < 0) {
        printf("Output (/dev/uinput) could not be opened. Are you root?");
        return 0;
    }
	createVirtualInput(fd_uinput, mapsArray, mapCount);

	// be sure to create a udev rule for this symlink!
	fd_i = open("/dev/joycon-l", O_RDONLY);
	if (fd_i < 0) {
        printf("Input could not be opened. Is your joycon connected?\n");
        return 0;
    }

	while (1) {
		read(fd_i, &eventData, sizeof(struct input_event));
		printf("\tEvent type: %d code: %d value: %x\n", eventData.type, eventData.code, eventData.value);
		matchInput(fd_uinput, eventData, mapsArray, mapCount);
	}
	
	//clean up
	for (int i = 0; i< mapCount; i++) {
		free(mapsArray[i]);
	}
	close(fd_i);
	ioctl(fd_uinput, UI_DEV_DESTROY);
	close(fd_uinput);

	return 0;
}
