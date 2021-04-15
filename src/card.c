#include "../include/card.h"

void cardCreate(char * cardName, char * cardDescription)
{
    Card *card = (Card*)calloc(1, sizeof(struct Card));
    card->cardID = instance.selectedBoard->cardIDCounter;
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

    if(instance.selectedBoard->baseNode==NULL)
    {
        instance.selectedBoard->baseNode=temp;
        instance.selectedBoard->cardIDCounter++;
    }
    else {
        cardNode *currNode;
        currNode = instance.selectedBoard->baseNode;
        while (currNode->next != NULL) {
            currNode = currNode->next;
        }
        currNode->next=temp;
    }
    instance.selectedBoard->numberOfCards++;
    printf("Card done\n");
}

void cardModifyName(int cardID, char* cardName) {

}

void cardModifyDescription(int cardID, char* cardDescription) {

}

void cardDelete(int CardId)
{
    cardNode *currNode;
    currNode = instance.selectedBoard->baseNode;
    cardNode  *temp;

    if (currNode->card->cardID == CardId){ //ha az elso a kitorlendo elem
        temp = currNode;
        instance.selectedBoard->baseNode=currNode;
        free(temp);
    }

    else {  //a kitorlendo elem a kozepen vagy a vegen van
        while (currNode->next != NULL) {
            temp=currNode->next;
            if(temp->card->cardID == CardId){ //akkor lepik be ha megtalaltuk az elemet
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
        if(currNode->card->cardID == CardId){ //akkor lepik be ha megtalaltuk az elemet
            currNode->card->user=(char *)calloc(strlen(userEmail)+1, sizeof (char));
            strcpy(currNode->card->user, userEmail);
            break;
        }
        currNode = currNode->next;
    }
}

void cardRemoveUser(int CardId, char *userEmail){
    cardNode *currNode;
    currNode = instance.selectedBoard->baseNode;
    while (currNode->next != NULL) {
        if(currNode->card->cardID == CardId){ //akkor lepik be ha megtalaltuk az elemet
            free(currNode->card->user);
            currNode->card->user = NULL;
            break;
        }
        currNode = currNode->next;
    }
}

void cardGetStatus(int CardId) {
    cardNode *currNode;
    currNode = instance.selectedBoard->baseNode;
    while (currNode->next != NULL) {
        if(currNode->card->cardID == CardId){ //akkor lepik be ha megtalaltuk az elemet
            switch (currNode->card->status) {
                case TODO: printf("\033[0;31m");
                    printf("TODO");
                    break;
                case WORKING: printf("\033[0;33m");
                    printf("WORKING"); break;
                case DONE: printf("\033[0;32m");
                    printf("DONE"); break;
            }
            printf("\33[0m");
        }
        currNode = currNode->next;
    }
}

void cardSetStatus(int CardId, enum Status status) {
    cardNode *currNode;
    currNode = instance.selectedBoard->baseNode;
    while (currNode->next != NULL) {
        if(currNode->card->cardID == CardId){ //akkor lepik be ha megtalaltuk az elemet
            currNode->card->status = status;
            break;
        }
        currNode = currNode->next;
    }
}

void cardUpdate(int cardID) {
    cardNode *currNode;
    currNode = instance.selectedBoard->baseNode;
    while (currNode->next != NULL) {
        if(currNode->card->cardID == cardID) { //akkor lepik be ha megtalaltuk az elemet
            if (currNode->card->status != DONE) {
                if (currNode->card->status == TODO) {
                    currNode->card->status = WORKING;
                }
                else if (currNode->card->status == WORKING) {
                    currNode->card->status = DONE;
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
        if(currNode->card->cardID == CardId){ //akkor lepik be ha megtalaltuk az elemet
           //kiiratas;
            break;
        }
        currNode = currNode->next;
    }
}

Card* cardGet(int i) {
    if (i < 0 || i >= instance.selectedBoard->numberOfCards) {
        return NULL;
    }

    cardNode* node = instance.selectedBoard->baseNode;
    int c = 0;
    while (node != NULL) {
        if (c == i) {
            return node->card;
        }

        c++;
        node = node->next;
    }

    return NULL;
}

void cardList() {
    if(instance.selectedBoard->numberOfCards==0)
    {
        printf("No cards in this board\n");
        return;
    }

    for (int i = 0; i < instance.selectedBoard->numberOfCards; i++) {
        Card* card = cardGet(i);
        for (int i = 0; i < CARD_BORDER_LENGTH; i++) {
            printf("-");
        }
        printf("\n");

        printf("%4d ", card->cardID);
        cardGetStatus(card->cardID);
        printf("%s\n", card->title);
        printf("%s\n\n", card->description);

        struct tm* tm;	// built-in structure to convert seconds into a datetime structure
        if ((tm = localtime(&card->timestamp)) == NULL) {
            printf("ERROR: Cannot convert seconds to datetime\n");
        }

        // 	Print out datetime structure into an easily readable form
        printf("[%04d-%02d-%02d %02d:%02d:%02d]\n",
               tm->tm_year+1900, tm->tm_mon, tm->tm_mday,
               tm->tm_hour, tm->tm_min, tm->tm_sec);

        for (int i = 0; i < CARD_BORDER_LENGTH; i++) {
            printf("-");
        }
        printf("\n");
    }
}