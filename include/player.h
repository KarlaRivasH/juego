#ifndef PLAYER_H
#define PLAYER_H

#include "room.h"

enum Direction { UP, DOWN, LEFT, RIGHT };

struct Player {
    int x;
    int y;
    bool hasKey;
    int currentRoom;
};

extern Player player;

void movePlayer(Direction dir);
void drawPlayer();
void erasePlayer(int x, int y);
void checkTile();
void drawInfo();

#endif
