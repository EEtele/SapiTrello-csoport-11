#ifndef SAPITRELLO_CSOPORT_11_BOARD_H
#define SAPITRELLO_CSOPORT_11_BOARD_H

#include <stdio.h>
#include <stdlib.h>

#include "defines.h"
#include "card.h"
#include "user.h"


typedef struct {
    char name[MAX_BOARD_NAME_LENGTH];
    cardNode *baseNode;
    int numberOfCards;
    int numberOfUsers;
    char** users;
} Board;

#endif //SAPITRELLO_CSOPORT_11_BOARD_H
