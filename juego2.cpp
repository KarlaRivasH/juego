#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>
using namespace std;

const int ROOM_WIDTH = 40;
const int ROOM_HEIGHT = 15;
const int TOTAL_ROOMS = 9; // más habitaciones, estilo laberinto 3x3

enum Direction { UP, DOWN, LEFT, RIGHT };
enum TileType { EMPTY, KEY, EXIT };

struct Player {
    int x = ROOM_WIDTH / 2;
    int y = ROOM_HEIGHT / 2;
    int roomX = 1; // posición en la cuadrícula de habitaciones
    int roomY = 1;
    bool hasKey = false;
};

struct Room {
    TileType tile = EMPTY;
};

Room rooms[3][3]; // 3x3 habitaciones
Player player;

// ------------- UTILIDADES DE CONSOLA -------------
void goToXY(int x, int y) {
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void hideCursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void clearLine(int y) {
    goToXY(0, y);
    cout << string(ROOM_WIDTH, ' ');
}

// ------------- DIBUJADO DE HABITACIÓN -------------

void drawRoom() {
    goToXY(0, 0);

    Room& currentRoom = rooms[player.roomY][player.roomX];

    for (int y = 0; y < ROOM_HEIGHT; y++) {
        for (int x = 0; x < ROOM_WIDTH; x++) {
            bool isWall = (y == 0 || y == ROOM_HEIGHT - 1 || x == 0 || x == ROOM_WIDTH - 1);
            bool isDoor =
                (y == ROOM_HEIGHT / 2 && (x == 0 || x == ROOM_WIDTH - 1)) ||
                (x == ROOM_WIDTH / 2 && (y == 0 || y == ROOM_HEIGHT - 1));

            if (isWall && !isDoor) {
                cout << "#"; // pared
            } else if (x == player.x && y == player.y) {
                cout << "@"; // jugador
            } else if (currentRoom.tile == KEY && x == ROOM_WIDTH / 2 && y == ROOM_HEIGHT / 2 - 2) {
                cout << "K";
            } else if (currentRoom.tile == EXIT && x == ROOM_WIDTH / 2 && y == ROOM_HEIGHT / 2 + 2) {
                cout << "E";
            } else {
                cout << " ";
            }
        }
        cout << "\n";
    }

    // Info
    clearLine(ROOM_HEIGHT);
    goToXY(0, ROOM_HEIGHT);
    cout << "📍 Habitacion [" << player.roomY << "," << player.roomX << "] | 🔑 Llave: " << (player.hasKey ? "Sí" : "No") << " | Q para salir";
}

// ------------- MOVIMIENTO -------------

void movePlayer(Direction dir) {
    switch (dir) {
        case UP:
            if (player.y > 1) player.y--;
            else if (player.y == 1 && player.x == ROOM_WIDTH / 2 && player.roomY > 0) {
                player.roomY--;
                player.y = ROOM_HEIGHT - 2;
            }
            break;
        case DOWN:
            if (player.y < ROOM_HEIGHT - 2) player.y++;
            else if (player.y == ROOM_HEIGHT - 2 && player.x == ROOM_WIDTH / 2 && player.roomY < 2) {
                player.roomY++;
                player.y = 1;
            }
            break;
        case LEFT:
            if (player.x > 1) player.x--;
            else if (player.x == 1 && player.y == ROOM_HEIGHT / 2 && player.roomX > 0) {
                player.roomX--;
                player.x = ROOM_WIDTH - 2;
            }
            break;
        case RIGHT:
            if (player.x < ROOM_WIDTH - 2) player.x++;
            else if (player.x == ROOM_WIDTH - 2 && player.y == ROOM_HEIGHT / 2 && player.roomX < 2) {
                player.roomX++;
                player.x = 1;
            }
            break;
    }
}

// ------------- LÓGICA DE LLAVE Y SALIDA -------------

void checkTile() {
    Room& currentRoom = rooms[player.roomY][player.roomX];

    if (currentRoom.tile == KEY &&
        player.x == ROOM_WIDTH / 2 && player.y == ROOM_HEIGHT / 2 - 2) {
        player.hasKey = true;
        currentRoom.tile = EMPTY;
        goToXY(0, ROOM_HEIGHT + 1);
        cout << "🔑 Has recogido la llave!";
    }

    else if (currentRoom.tile == EXIT &&
        player.x == ROOM_WIDTH / 2 && player.y == ROOM_HEIGHT / 2 + 2) {
        if (player.hasKey) {
            goToXY(0, ROOM_HEIGHT + 1);
            cout << "\n\n🎉 ¡Ganaste! Encontraste la salida con la llave.\n\n";
            exit(0);
        } else {
            goToXY(0, ROOM_HEIGHT + 1);
            cout << "🚪 Necesitas la llave para salir.";
        }
    } else {
        clearLine(ROOM_HEIGHT + 1);
    }
}

// ------------- BUCLE DEL JUEGO -------------

void gameLoop() {
    drawRoom();
    while (true) {
        if (_kbhit()) {
            char ch = _getch();
            switch (ch) {
                case 72: movePlayer(UP); break;    // flecha arriba
                case 80: movePlayer(DOWN); break;  // flecha abajo
                case 75: movePlayer(LEFT); break;  // flecha izquierda
                case 77: movePlayer(RIGHT); break; // flecha derecha
                case 'q': return;                  // salir
            }
            checkTile();
            drawRoom();
        }
        Sleep(30);
    }
}

// ------------- INICIALIZACIÓN DEL JUEGO -------------

void initGame() {
    srand(time(0));
    int keyX = rand() % 3, keyY = rand() % 3;
    int exitX, exitY;

    do {
        exitX = rand() % 3;
        exitY = rand() % 3;
    } while (exitX == keyX && exitY == keyY);

    rooms[keyY][keyX].tile = KEY;
    rooms[exitY][exitX].tile = EXIT;
}

// ------------- MAIN -------------
int main() {
    hideCursor();
    initGame();
    gameLoop();
    return 0;
}
