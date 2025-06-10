#include <iostream>
#include <windows.h>
#include <conio.h>
#include "player.h"
#include "room.h"
#include "utils.h"
#include <game.h>
using namespace std; 

void movePlayer(Direction dir) {
    int prevX = player.x;
    int prevY = player.y;

    switch (dir) {
        case UP:
            if (player.y > 1) player.y--;
            else if (player.y == 1 && player.x == ROOM_WIDTH / 2 && player.currentRoom > 0) {
                player.currentRoom--;
                player.y = ROOM_HEIGHT - 2;
                drawRoom();
                return;
            }
            break;
        case DOWN:
            if (player.y < ROOM_HEIGHT - 2) player.y++;
            else if (player.y == ROOM_HEIGHT - 2 && player.x == ROOM_WIDTH / 2 && player.currentRoom < TOTAL_ROOMS - 1) {
                player.currentRoom++;
                player.y = 1;
                drawRoom();
                return;
            }
            break;
        case LEFT:
            if (player.x > 1) player.x--;
            break;
        case RIGHT:
            if (player.x < ROOM_WIDTH - 2) player.x++;
            break;
    }

    erasePlayer(prevX, prevY);
    drawPlayer();
    drawInfo();
}

void drawPlayer() {
    goToXY(player.x, player.y);
    cout << "@";
}

void erasePlayer(int x, int y) {
    goToXY(x, y);
    cout << " ";
}

void drawInfo() {
    goToXY(0, ROOM_HEIGHT);
    cout << "Room: " << player.currentRoom + 1 << "/" << TOTAL_ROOMS;
    cout << " | Key: " << (player.hasKey ? "Yes" : "No") << "      ";
}

void checkTile() {
    if (rooms[player.currentRoom].tile == KEY &&
        player.x == ROOM_WIDTH / 2 && player.y == ROOM_HEIGHT / 2 - 2) {
        player.hasKey = true;
        rooms[player.currentRoom].tile = EMPTY;
        goToXY(player.x, player.y); cout << "@";
    }

    if (rooms[player.currentRoom].tile == EXIT &&
        player.x == ROOM_WIDTH / 2 && player.y == ROOM_HEIGHT / 2 + 2) {
        if (player.hasKey) {
            system("cls");
            cout << "\n\n🎉 ¡Ganaste! Encontraste la salida con la llave.\n\n";
            exit(0);
        } else {
            goToXY(0, ROOM_HEIGHT + 1);
            cout << "🚪 Necesitas la llave para salir.";
        }
    }
}
