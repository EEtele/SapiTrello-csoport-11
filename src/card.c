#include "../include/card.h"

void cardCreate(char * cardName, char * cardDescription)
{
    Card *card;
    srand(time(0));
    card->cardID = rand()%10000;
    card->title=(char *)calloc(strlen(cardName)+1, sizeof(char));
    card->description=(char *)calloc(strlen(cardDescription)+1, sizeof(char));
    strcpy(card->title, cardName);
    strcpy(card->description, cardDescription);
    card->timestamp = time(0);
    card->status=TODO;
    card->user=NULL;
    card->numberOfUserLog=0;

    cardNode* temp=(cardNode*)malloc(sizeof(cardNode));
    (*temp).card=card;
    (*temp).next=NULL;

    if(instance.selectedBoard->baseNode=NULL)
    {
        instance.selectedBoard->baseNode=temp;
    }
    else {
        cardNode *currNode;
        currNode = instance.selectedBoard->baseNode;
        while (currNode->next != NULL) {
            currNode = currNode->next;
        }
        currNode->next=temp;
    }
}

void cardDelete(int CardId)
{
    cardNode *currNode;
    currNode = instance.selectedBoard->baseNode;
    cardNode  *temp;

    if (currNode->card.cardId == CardId){ //ha az elso a kitorlendo elem
        temp = currNode;
        instance.selectedBoard->baseNode=currNode;
        free(temp);
    }

    else {  //a kitorlendo elem a kozepen vagy a vegen van
        while (currNode->next != NULL) {
            temp=currNode->next;
            if(temp->card.cardId == CardId){ //akkor lepik be ha megtalaltuk az elemet
                currNode->next = temp->next;
                free(temp); break;
            }
            else {
                currNode = currNode->next;
            }
        }
    }
}

void cardAssignUser(int CardId, char * userEmail){
    cardNode *currNode;
    currNode = instance.selectedBoard->baseNode;
    while (currNode->next != NULL) {
        if(currNode->card.cardId == CardId){ //akkor lepik be ha megtalaltuk az elemet
            currNode->card.user=(char *)calloc(strlen(userEmail)+1, sizeof (char));
            strcpy(currNode->card.user, userEmail);
            break;
        }
        currNode = currNode->next;
    }
}

void cardRemoveUser(int CardId, char *userEmail){
    cardNode *currNode;
    currNode = instance.selectedBoard->baseNode;
    while (currNode->next != NULL) {
        if(currNode->card.cardId == CardId){ //akkor lepik be ha megtalaltuk az elemet
            free(currNode->card.user);
            currNode->card.user = NULL;
            break;
        }
        currNode = currNode->next;
    }
}

void cardGetStatus(int CardId) {
    cardNode *currNode;
    currNode = instance.selectedBoard->baseNode;
    while (currNode->next != NULL) {
        if(currNode->card.cardId == CardId){ //akkor lepik be ha megtalaltuk az elemet
            printf("\n%s", currNode->card.status);
            break;
        }
        currNode = currNode->next;
    }
}

void cardSetStatus(int CardId, enum Status status) {
    cardNode *currNode;
    currNode = instance.selectedBoard->baseNode;
    while (currNode->next != NULL) {
        if(currNode->card.cardId == CardId){ //akkor lepik be ha megtalaltuk az elemet
            currNode->card.status = status;
            break;
        }
        currNode = currNode->next;
    }
}

void cardUpdate(int cardID) {
    cardNode *currNode;
    currNode = instance.selectedBoard->baseNode;
    while (currNode->next != NULL) {
        if(currNode->card.cardId == cardID) { //akkor lepik be ha megtalaltuk az elemet
            if (currNode->card.status != DONE) {
                if (currNode->card.status == TODO) {
                    currNode->card.status = WORKING;
                }
                else if (currNode->card.status == WORKING) {
                    currNode->card.status = DONE;
                    }
                }
            }
                break;
        }
        currNode = currNode->next;
    }

void cardGetUserLog(int CardId){
    cardNode *currNode;
    currNode = instance.selectedBoard->baseNode;
    while (currNode->next != NULL) {
        if(currNode->card.cardId == CardId){ //akkor lepik be ha megtalaltuk az elemet
           //kiiratas;
            break;
        }
        currNode = currNode->next;
    }
}


