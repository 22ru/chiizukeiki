#include "header.h"

int loadKeymap(keyMap *mapsArrayPtr[20]) {
    FILE *fp;
    int mapCount = 0;

	printf("Mapsarray location inside function: %x\n", mapsArrayPtr);

    fp = fopen("default.map", "r");
	if (!fp) {
        printf("Map profile could not be opened.");
        return 0;
    }
	while (!feof(fp)) {
		keyMap *mapPtr = malloc(sizeof(keyMap));

		keyMap map;
		fscanf(fp, "%d%d%d%d%d%d", &(map.eventType),&(map.eventCode),&(map.eventValue),&(map.result[0]),&(map.result[1]),&(map.result[2]));
		//printf("Read: %d %d %d %d %d %d\n", map.eventType, map.eventCode, map.eventValue, map.result[0], map.result[1], map.result[2]);
		memcpy(mapPtr, &map, sizeof(keyMap));
		//printf("Copied: %d %d %d %d %d %d\n", mapPtr->eventType, mapPtr->eventCode, mapPtr->eventValue, mapPtr->result[0], mapPtr->result[1], mapPtr->result[2]);
		printf("Copying mapPtr to location: %x\n", &mapsArrayPtr[mapCount]);

		mapsArrayPtr[mapCount] = mapPtr;
		//printf("Location of map #%d: %x\n", mapCount, );
        printf("Copied: %d %d %d %d %d %d\n", mapsArrayPtr[mapCount]->eventType, mapsArrayPtr[mapCount]->eventCode, mapsArrayPtr[mapCount]->eventValue, mapsArrayPtr[mapCount]->result[0], mapsArrayPtr[mapCount]->result[1], mapsArrayPtr[mapCount]->result[2]);

		mapCount++;
	}

	fclose(fp);
    return mapCount;
}