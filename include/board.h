#ifndef SAPITRELLO_CSOPORT_11_BOARD_H
#define SAPITRELLO_CSOPORT_11_BOARD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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


void boardCreate(char* boardName);
int boardExists(char* boardName);
void boardModify(char* newName);
void boardDelete(char* targetName);
void boardSelect(char* boardName);
void sortCardsStatusDate();
void boardList();
int boardContainsUser(char* email);
void boardAddUser(char* email);
void boardListUsers();
void boardRemoveUser(char* email);


#endif //SAPITRELLO_CSOPORT_11_BOARD_H
