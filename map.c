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