#include "../include/card.h"

void cardCreate(char * cardName, char * cardDescription)
{
    Card *card = (Card*)calloc(1, sizeof(struct Card));
    if (card == NULL) {
        printf("Could not allocate card\n");
        return;
    }

    card->cardID = instance.selectedBoard->cardIDCounter;
    strcpy(card->title, cardName);
    strcpy(card->description, cardDescription);
    card->timestamp = time(0);
    card->status=TODO;
    card->numberOfUserLog=0;

    cardNode* temp=(cardNode*)calloc(1, sizeof(cardNode));
    if (temp == NULL) {
        printf("Could not allocate node\n");
    }
    (*temp).card=card;
    (*temp).next=NULL;

    if(instance.selectedBoard->baseNode==NULL)
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

    instance.selectedBoard->cardIDCounter++;
    instance.selectedBoard->numberOfCards++;
    printf("Card created with ID %d\n", card->cardID);
}

void cardModifyName(int cardID, char* cardName) {
    cardNode *currNode = instance.selectedBoard->baseNode;
    while (currNode != NULL) {
        if(currNode->card->cardID == cardID){ //akkor lepik be ha megtalaltuk az elemet
            strcpy(currNode->card->title, cardName);
            printf("Card name modified\n");
            return;
        }
        currNode = currNode->next;
    }

    printf("Could not find card\n");
}

void cardModifyDescription(int cardID, char* cardDescription) {
    cardNode *currNode = instance.selectedBoard->baseNode;
    while (currNode != NULL) {
        if(currNode->card->cardID == cardID){ //akkor lepik be ha megtalaltuk az elemet
            strcpy(currNode->card->description, cardDescription);
            printf("Card description modified\n");
            return;
        }
        currNode = currNode->next;
    }
    printf("Could not find card\n");
}

void cardDelete(int CardId)
{
    cardNode *currNode;
    currNode = instance.selectedBoard->baseNode;
    cardNode  *temp;

    if (currNode->card->cardID == CardId){ //ha az elso a kitorlendo elem
        temp = currNode;
        instance.selectedBoard->baseNode=currNode->next;
        free(temp->card->userLog);
        free(temp);
        instance.selectedBoard->numberOfCards--;
        printf("Card successfully deleted\n");
        return;
    } else {  //a kitorlendo elem a kozepen vagy a vegen van
        while (currNode != NULL) {
            if(currNode->card->cardID == CardId){ //akkor lepik be ha megtalaltuk az elemet
                temp->next = currNode->next;
                free(currNode->card->userLog);
                free(currNode);
                instance.selectedBoard->numberOfCards--;
                printf("Card successfully deleted\n");
                return;
            }
            else {
                temp = currNode;    // temp holds previous node
                currNode = currNode->next;
            }
        }
    }
    printf("Could not find card\n");
}

void cardAssignUser(int CardId, char * userEmail){
    cardNode *currNode;
    currNode = instance.selectedBoard->baseNode;
    if (!boardContainsUser(userEmail)) {
        printf("Board doesnt contain this user\n");
        return;
    }
    while (currNode != NULL) {
        if(currNode->card->cardID == CardId){ //akkor lepik be ha megtalaltuk az elemet
            strcpy(currNode->card->user, userEmail);
            printf("Assigned user %s to card\n", userEmail);

            currNode->card->numberOfUserLog++;
            if (currNode->card->numberOfUserLog == 0) {
                currNode->card->userLog = (char**)calloc(1, sizeof(char*));
            } else {
                currNode->card->userLog = (char **) realloc(currNode->card->userLog,
                                                            currNode->card->numberOfUserLog * (sizeof(char *)));
            }
            currNode->card->userLog[currNode->card->numberOfUserLog-1] = (char*)calloc(MAX_USER_EMAIL_LENGTH, sizeof(char));
            strcpy(currNode->card->userLog[currNode->card->numberOfUserLog-1], userEmail);
            return;
        }
        currNode = currNode->next;
    }

    printf("Could not find card\n");
}

void cardRemoveUser(int CardId, char *userEmail){
    cardNode *currNode;
    currNode = instance.selectedBoard->baseNode;
    while (currNode != NULL) {
        if(currNode->card->cardID == CardId){ //akkor lepik be ha megtalaltuk az elemet
            if (strcmp(currNode->card->user, "") != 0) {
                strcpy(currNode->card->user, "");
                printf("Removed user from card\n");
            }
            return;
        }
        currNode = currNode->next;
    }

    printf("Could not find card\n");
}

void cardGetStatus(int CardId) {
    cardNode *currNode;
    currNode = instance.selectedBoard->baseNode;
    while (currNode != NULL) {
        if(currNode->card->cardID == CardId){ //akkor lepik be ha megtalaltuk az elemet
            switch (currNode->card->status) {
                case TODO:
                    printf("TODO"); break;
                case WORKING:
                    printf("WORKING"); break;
                case DONE:
                    printf("DONE"); break;
            }
            return;
        }
        currNode = currNode->next;
    }

    printf("Could not find card\n");
}

void cardSetStatus(int CardId, enum Status status) {
    cardNode *currNode;
    currNode = instance.selectedBoard->baseNode;
    while (currNode != NULL) {
        if(currNode->card->cardID == CardId){ //akkor lepik be ha megtalaltuk az elemet
            currNode->card->status = status;
            printf("Card status updated\n");
            return;
        }
        currNode = currNode->next;
    }

    printf("Could not find card\n");
}

void cardUpdate(int cardID) {
    cardNode *currNode;
    currNode = instance.selectedBoard->baseNode;
    while (currNode != NULL) {
        if(currNode->card->cardID == cardID) { //akkor lepik be ha megtalaltuk az elemet
            if (currNode->card->status != DONE) {
                if (currNode->card->status == TODO) {
                    currNode->card->status = WORKING;
                    printf("Updated status to WORKING\n");
                    return;
                }
                else if (currNode->card->status == WORKING) {
                    currNode->card->status = DONE;
                    printf("Updated status to DONE\n");
                    return;
                }
            }
            printf("Card is already DONE\n");
            return;
        }
        currNode = currNode->next;
    }
    printf("Could not find card\n");
}

void cardGetUserLog(int CardId){
    cardNode *currNode;
    currNode = instance.selectedBoard->baseNode;
    while (currNode != NULL) {
        if(currNode->card->cardID == CardId){ //akkor lepik be ha megtalaltuk az elemet
           if (currNode->card->numberOfUserLog == 0) {
               printf("Empty user log\n");
               return;
           }
            for (int i = 0; i < currNode->card->numberOfUserLog; i++) {
               printf("%s\n", currNode->card->userLog[i]);
           }
           return;
        }
        currNode = currNode->next;
    }
    printf("Could not find card\n");
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
        printf(" %s", card->title);
        printf(" (%s)\n", card->user);
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