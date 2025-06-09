#ifndef ROOM_H
#define ROOM_H

const int ROOM_WIDTH = 40;
const int ROOM_HEIGHT = 15;
const int TOTAL_ROOMS = 5;

enum TileType { EMPTY, KEY, EXIT };

struct Room {
    TileType tile;
};

extern Room rooms[TOTAL_ROOMS];

void drawBorders();
void drawStaticTiles();

#endif
