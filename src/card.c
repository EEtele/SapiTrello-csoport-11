#include "../include/card.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Card cardCreate(char * cardName, char * cardDescription, char * user)
{
    /*
    int cardID;	// generate using rand()
    //		(NOTE: will have to verify availability of generated ID)

    char* title;
    char* description;
//    time_t timestamp;	//	Date when card was created
    enum Status status;
    char* user;	// Assigned user (store email); board must contain this user
    char** userLog;	// Store emails of all users who worked on t */

    Card card;
    srand(time(0));
    card.cardID = rand()%1000;
    card.title=(char *)calloc(strlen(cardName)+1, sizeof(char));
    card.description=(char *)calloc(strlen(cardDescription)+1, sizeof(char));
    strcpy(card.title, cardName);
    strcpy(card.description, cardDescription);
    card.status=TODO;
    card.user=(char *)calloc(strlen(user)+1, sizeof(char));
    strcpy(card.user, user);
    card.userLogCounter=0;
    return card;
}

void cardDelete(Card * card)
{
    free(card);
}

char * cardAssignUser(Card * card)
{
    return card->user;
}

void cardModifyUser(Card * card, char * user)
{
    card->userLogCounter++;
    void *pointer;
    pointer = realloc(card->userLog, card->userLogCounter * sizeof(char *));
    card->userLog = pointer;
    card->user=(char *)calloc( strlen(user), sizeof(char));
    card->user=user;
}

enum Status cardGetStatus(Card * card)
{
    return card->status;
}

void cardSetStatus(Card * card, enum Status status)
{
    card->status=status;
}