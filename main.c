#include "header.h"

// https://web.archive.org/web/20190327023254/http://www.infradead.org/~mchehab/kernel_docs_pdf/linux-input.pdf
// https://web.archive.org/web/20160430145509/http://thiemonge.org/getting-started-with-uinput


int main (int argc, char **argv) {
	int fd_i, fd_o;
	struct input_event data;
	int mapCount=0;
	keyMap *mapsArray[20];

	if (argc > 1) {
		printf("Loading from file %s\n", argv[1]);
		mapCount = loadKeymap(mapsArray, argv[1]);
	} else {
		mapCount = loadKeymap(mapsArray, "default.map");
	}

	for (int i = 0; i< mapCount; i++) {
		printf("Map #%d, memory location: %x\n", i, &mapsArray[i]);
		printf("\t%d %d %d %d %d %d\n", mapsArray[i]->eventType, mapsArray[i]->eventCode, mapsArray[i]->eventValue, mapsArray[i]->result[0], mapsArray[i]->result[1], mapsArray[i]->result[2]);
	}



	//clean up
	for (int i = 0; i< mapCount; i++) {
		free(mapsArray[i]);
	}

	return 0;
}
