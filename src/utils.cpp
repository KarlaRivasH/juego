#include <windows.h>
#include "utils.h"
#include <iostream>
using namespace std; 
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
void setConsoleSize(int width, int height) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD bufferSize = { short(width), short(height) };
    if (!SetConsoleScreenBufferSize(hOut, bufferSize)) {
        DWORD err = GetLastError();
        cout << "Error al cambiar tamaño buffer: " << err << std::endl;
    }

    SMALL_RECT windowSize = {0, 0, short(width - 1), short(height - 1)};
    if (!SetConsoleWindowInfo(hOut, TRUE, &windowSize)) {
        DWORD err = GetLastError();
        cout << "Error al cambiar tamaño ventana: " << err << std::endl;
    }
}
