#include "game.h"
#include "utils.h"

int main()
{
    hideCursor();
    initGame();
    gameLoop();

    return 0;
}
