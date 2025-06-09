#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>
using namespace std;

const int ROOM_WIDTH = 40;
const int ROOM_HEIGHT = 15;
const int TOTAL_ROOMS = 5;

enum Direction { UP, DOWN, LEFT, RIGHT };
enum TileType { EMPTY, KEY, EXIT };

struct Player {
    int x = ROOM_WIDTH / 2;
    int y = ROOM_HEIGHT / 2;
    bool hasKey = false;
    int currentRoom = 0;
};

struct Room {
    TileType tile = EMPTY;
};

Room rooms[TOTAL_ROOMS];
Player player;

void goToXY(int x, int y) {
    COORD coord = { short(x), short(y) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void hideCursor() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    GetConsoleCursorInfo(hOut, &cci);
    cci.bVisible = FALSE;
    SetConsoleCursorInfo(hOut, &cci);
}

void drawBorders() {
    for (int y = 0; y < ROOM_HEIGHT; y++) {
        for (int x = 0; x < ROOM_WIDTH; x++) {
            goToXY(x, y);
            if (y == 0 || y == ROOM_HEIGHT - 1 || x == 0 || x == ROOM_WIDTH - 1) {
                if ((y == ROOM_HEIGHT / 2 && (x == 0 || x == ROOM_WIDTH - 1)) ||
                    (x == ROOM_WIDTH / 2 && (y == 0 || y == ROOM_HEIGHT - 1))) {
                    cout << " "; // Door
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

void drawRoom() {
    system("cls"); // Only on first draw
    drawBorders();
    drawStaticTiles();
    drawPlayer();
    drawInfo();
}

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

void gameLoop() {
    drawRoom();
    while (true) {
        if (_kbhit()) {
            char ch = _getch();
            switch (ch) {
                case 72: movePlayer(UP); break;
                case 80: movePlayer(DOWN); break;
                case 75: movePlayer(LEFT); break;
                case 77: movePlayer(RIGHT); break;
                case 'q': return;
            }
            checkTile();
        }
        Sleep(50);
    }
}

void initGame() {
    srand(time(0));
    int keyRoom = rand() % TOTAL_ROOMS;
    int exitRoom;
    do {
        exitRoom = rand() % TOTAL_ROOMS;
    } while (exitRoom == keyRoom);

    rooms[keyRoom].tile = KEY;
    rooms[exitRoom].tile = EXIT;
}

int main() {
    hideCursor();
    initGame();
    gameLoop();
    return 0;
}
