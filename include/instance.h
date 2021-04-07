#ifndef SAPITRELLO_CSOPORT_11_INSTANCE_H
#define SAPITRELLO_CSOPORT_11_INSTANCE_H

#include <stdlib.h>

#include "user.h"
#include "board.h"

struct Instance {
    Board* selectedBoard;   // Pointer to currently selected board, null by default

    int numberOfBoards;
    Board* boards;
    int numberOfUsers;
    User* users;
} instance;
// Only one instance per process

int instanceLoad();
int instanceWrite();

#endif //SAPITRELLO_CSOPORT_11_INSTANCE_H
