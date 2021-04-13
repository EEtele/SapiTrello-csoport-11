#ifndef SAPITRELLO_CSOPORT_11_BOARD_H
#define SAPITRELLO_CSOPORT_11_BOARD_H

#include <stdio.h>
#include <stdlib.h>

#include "defines.h"
#include "card.h"
#include "user.h"


typedef struct Board {
    char name[MAX_BOARD_NAME_LENGTH];
    int numberOfCards;
    struct cardNode *baseNode;
    int numberOfUsers;
    char** users;
    int cardIDCounter;
} Board;

#endif //SAPITRELLO_CSOPORT_11_BOARD_H
