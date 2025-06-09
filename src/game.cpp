#include <cstdlib>
#include <ctime>
#include <iostream>
#include "game.h"
#include "room.h"
#include "player.h"
#include <conio.h>
#include <windows.h>
#include <utils.h>

Player player = {ROOM_WIDTH / 2, ROOM_HEIGHT / 2, false, 0};
Room rooms[TOTAL_ROOMS];

void initGame()
{
    setConsoleSize(200, 150);

    srand(static_cast<unsigned>(time(0)));
    int keyRoom = rand() % TOTAL_ROOMS;
    int exitRoom;
    do
    {
        exitRoom = rand() % TOTAL_ROOMS;
    } while (exitRoom == keyRoom);

    for (int i = 0; i < TOTAL_ROOMS; i++)
    {
        rooms[i].tile = EMPTY;
    }

    rooms[keyRoom].tile = KEY;
    rooms[exitRoom].tile = EXIT;
}

void drawRoom()
{
    system("cls");
    drawBorders();
    drawStaticTiles();
    drawPlayer();
    drawInfo();
}

void gameLoop()
{
    drawRoom();
    while (true)
    {
        if (_kbhit())
        {
            char ch = _getch();
            switch (ch)
            {
            case 72:
                movePlayer(UP);
                break;
            case 80:
                movePlayer(DOWN);
                break;
            case 75:
                movePlayer(LEFT);
                break;
            case 77:
                movePlayer(RIGHT);
                break;
            case 'q':
                return;
            }
            checkTile();
        }
        Sleep(50);
    }
}
