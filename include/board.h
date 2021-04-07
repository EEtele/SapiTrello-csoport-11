#ifndef SAPITRELLO_CSOPORT_11_BOARD_H
#define SAPITRELLO_CSOPORT_11_BOARD_H

#include "defines.h"
#include "card.h"

typedef struct {
    char* name;

    int numberOfCards;
    Card* cards;    // Linked list
    int numberOfUsers;
    char** users;
} Board;

#endif //SAPITRELLO_CSOPORT_11_BOARD_H
