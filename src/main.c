#include "../include/instance.h"
#include "../include/terminal.h"

int main() {
    //instanceLoad();

    instance.selectedBoard = NULL;
    instance.numberOfBoards = 0;
    instance.boards = NULL;
    instance.numberOfUsers = 0;
    instance.users = NULL;

    // Terminal loop
    terminalLoop();

    //instanceWrite();
    return 0;
}
