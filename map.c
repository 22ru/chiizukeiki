#include "header.h"

int loadKeymap(keyMap **mapsArrayPtr, char *filename) {
    FILE *fp;
    int mapCount = 0;

    fp = fopen(filename, "r");
	if (!fp) {
        printf("Map profile could not be opened.\n");
        return 0;
    }
	while (!feof(fp)) {
		keyMap *mapPtr = malloc(sizeof(keyMap));

		fscanf(fp, "%d%d%d%d%d%d", &mapPtr->eventType, &mapPtr->eventCode, &mapPtr->eventValue, &mapPtr->result[0], &mapPtr->result[1], &mapPtr->result[2]);

		mapsArrayPtr[mapCount] = mapPtr;
		mapCount++;
	}

	fclose(fp);
    return mapCount;
}

void printKeyMap(keyMap **mapsArrayPtr, int mapCount) {
		for (int i = 0; i < mapCount; i++) {
		printf("Map #%d, memory location: %x\n", i, &mapsArrayPtr[i]);
		printf("\t%d %d %d %d %d %d\n", mapsArrayPtr[i]->eventType, mapsArrayPtr[i]->eventCode, mapsArrayPtr[i]->eventValue, mapsArrayPtr[i]->result[0], mapsArrayPtr[i]->result[1], mapsArrayPtr[i]->result[2]);
	}
}

void matchInput(int fd, struct input_event input, keyMap **mapsArrayPtr, int mapCount) {
	// ignore these events
	if (input.type == 0 || input.type == 4 || input.value == 2 || input.value == 0) {
		return;
	}
	for (int i = 0; i < mapCount; i++) {
		// in order of specificity
		// It's unlikely an event code won't match the event type
		// (at least for the joycon), so I will skip checking it.
		if (input.code == mapsArrayPtr[i]->eventCode && input.value == mapsArrayPtr[i]->eventValue) {
			printf("\tOutputting keys %d, %d, %d\n", mapsArrayPtr[i]->result[0],mapsArrayPtr[i]->result[1],mapsArrayPtr[i]->result[2]);
			sendChars(fd, mapsArrayPtr[i]->result);
		}
	}
}