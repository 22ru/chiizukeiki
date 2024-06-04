#include "header.h"

int loadKeymap(keyMap **mapsArrayPtr, char *filename) {
    FILE *fp;
    int mapCount = 0;

    fp = fopen(filename, "r");
	if (!fp) {
        printf("Map profile could not be opened. No output will be sent.\n");
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
	static int analog[2];
	int val;

	// ignore these events. I don't see any occuring anymore, so I'll skip this
	if (input.type == 0 || input.type == 4) {
		return;
	}

	//case: type 3, analog stick go-no-go
	// setting 3 levels for each analog axis
	if (input.type == 3) {
		/*printf("Analog input: ");
		if (input.code) {
			printf("y");
		} else {
			printf("x");
		}
		printf(" value: %d\n", input.value);
		*/
		// come back to this and optimize it pls
		if (input.value > 25000) {
			val = 1;
		} else if (input.value < -25000) {
			val = -1;
		} else {
			val = 0;
		}
 		//printf("curr val: %d, last val: %d\n", val, analog[input.code]);
		if (analog[input.code] == val) {
			// no-go if value remains the same
			return;
		} else {
			analog[input.code] = val;

			for (int i = 0; i < mapCount; i++) {
				if (input.code == mapsArrayPtr[i]->eventCode && val == mapsArrayPtr[i]->eventValue) {
					printf("Outputting and releasing keys %d, %d, %d\n", mapsArrayPtr[i]->result[0],mapsArrayPtr[i]->result[1],mapsArrayPtr[i]->result[2]);
					sendChars(fd, mapsArrayPtr[i]->result, 1);
					sendChars(fd, mapsArrayPtr[i]->result, 0);
				}
			}
		}
	}

	for (int i = 0; i < mapCount; i++) {
		// in order of specificity
		// event code is definitely 1 at this point
		if (input.code == mapsArrayPtr[i]->eventCode && input.value == mapsArrayPtr[i]->eventValue) {
			if (mapsArrayPtr[i]->eventValue == 2) {
				printf("Holding keys %d, %d, %d\n", mapsArrayPtr[i]->result[0],mapsArrayPtr[i]->result[1],mapsArrayPtr[i]->result[2]);
				sendChars(fd, mapsArrayPtr[i]->result, 2);
			} else if (mapsArrayPtr[i]->eventValue == 0) {
				printf("Releasing held keys %d, %d, %d\n", mapsArrayPtr[i]->result[0],mapsArrayPtr[i]->result[1],mapsArrayPtr[i]->result[2]);
				sendChars(fd, mapsArrayPtr[i]->result, 0);
			} else {
				printf("Outputting keys %d, %d, %d\n", mapsArrayPtr[i]->result[0],mapsArrayPtr[i]->result[1],mapsArrayPtr[i]->result[2]);
				sendChars(fd, mapsArrayPtr[i]->result, 1);
			}
		}
	}
}