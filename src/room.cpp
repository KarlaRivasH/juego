#include <iostream>
#include "room.h"
#include "utils.h"
#include <player.h>
using namespace std;

void drawBorders() {
    for (int y = 0; y < ROOM_HEIGHT; y++) {
        for (int x = 0; x < ROOM_WIDTH; x++) {
            goToXY(x, y);
            if (y == 0 || y == ROOM_HEIGHT - 1 || x == 0 || x == ROOM_WIDTH - 1) {
                if ((y == ROOM_HEIGHT / 2 && (x == 0 || x == ROOM_WIDTH - 1)) ||
                    (x == ROOM_WIDTH / 2 && (y == 0 || y == ROOM_HEIGHT - 1))) {
                    cout << " ";
                } else {
                    cout << "#";
                }
            } else {
                cout << " ";
            }
        }
    }
}

void drawStaticTiles() {
    if (rooms[player.currentRoom].tile == KEY) {
        goToXY(ROOM_WIDTH / 2, ROOM_HEIGHT / 2 - 2);
        cout << "K";
    }
    if (rooms[player.currentRoom].tile == EXIT) {
        goToXY(ROOM_WIDTH / 2, ROOM_HEIGHT / 2 + 2);
        cout << "E";
    }
}
