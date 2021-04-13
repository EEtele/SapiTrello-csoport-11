#ifndef SAPITRELLO_CSOPORT_11_CARD_H
#define SAPITRELLO_CSOPORT_11_CARD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "user.h"

enum Status {
    TODO, WORKING, DONE
};

typedef struct Card {
    int cardID;

    char* title;
    char* description;
    time_t timestamp;	//	Date when card was created
    enum Status status;
    char* user;	// Assigned user (store email); Board must contain this user
    char** userLog;	// Store emails of all users who worked on this card
    int numberOfUserLog; //hany email van a userLogban

} Card;

typedef struct cardNode{
    Card *card;
    struct cardNode* next;
}cardNode;

void cardCreate(char * cardName, char * cardDescription);
void cardModifyName(int cardID, char* cardName);
void cardModifyDescription(int cardID, char* cardDescription);
void cardDelete( int CardId);
void cardAssignUser(int CardId, char * userEmail);
void cardRemoveUser(int CardId, char *userEmail);
void cardUpdate(int cardID);
void cardSetStatus(int CardId, enum Status status);
void cardGetStatus(int CardId);
void cardGetUserLog(int CardId);
Card* cardGet(int i);
void cardList();

#endif //SAPITRELLO_CSOPORT_11_CARD_H
