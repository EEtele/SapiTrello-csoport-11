#ifndef SAPITRELLO_CSOPORT_11_INSTANCE_H
#define SAPITRELLO_CSOPORT_11_INSTANCE_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <direct.h>

#include "user.h"
#include "board.h"
#include "defines.h"

struct Instance {
    struct Board* selectedBoard;   // Pointer to currently selected Board, null by default

    int numberOfBoards;
    struct Board* boards;
    int numberOfUsers;
    struct User* users;
} instance;
// Only one instance per process

int instanceLoad();

int instanceWrite();

#endif //SAPITRELLO_CSOPORT_11_INSTANCE_H
