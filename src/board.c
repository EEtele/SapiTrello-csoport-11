#include "../include/board.h"

void boardCreate(char* boardName)
{
    Board* tempB=(Board*)calloc(1,sizeof(Board));
    if (tempB == NULL) {
        printf("Cannot allocate Board\n");
        return;
    }

    tempB->cardIDCounter = 0;
    strcpy((*tempB).name, boardName);
    if (instance.boards == NULL) {
        instance.boards = (Board*)calloc(1, sizeof(Board));
        if (instance.boards == NULL) {
            printf("Could not allocate boards array\n");
        }
        instance.boards[0] = *tempB;
        instance.numberOfBoards=1;
    } else {
        if(boardExists(boardName)!=-1){
            printf("Board already exists\n");
            return;}
        Board* ptr = instance.boards;
        int n = instance.numberOfBoards;
        Board* newPtr = (Board*)realloc(ptr, (n+1)*sizeof(Board));
        if (newPtr == NULL) {
            printf("Could not realloc boards array\n");
        }
        instance.boards = newPtr;
        instance.boards[n] = *tempB;
        instance.numberOfBoards++;
    }
    printf("Board created\n");
    boardSelect(tempB->name);
}

int boardExists(char* boardName)
{
    for(int i=0;i<instance.numberOfBoards;i++)
    {
        if(strcmp(instance.boards[i].name,boardName)==0)
        {
            return i;
        }
    }
    return -1;
}

void boardModify(char* newName)
{
    strcpy(instance.selectedBoard->name,newName);
    printf("Board name modified\n");
}

void boardSelect(char* boardName)
{
    for(int i=0;i<instance.numberOfBoards;i++)
    {
        if(strcmp(instance.boards[i].name,boardName)==0)
        {
            instance.selectedBoard=&instance.boards[i];
            printf("Board selected\n");
            return;
        }
    }

    printf("Could not find board\n");
}

void boardDelete(char* targetName)
{
    int i;
    for(i=0;i<instance.numberOfBoards;++i)
    {
        if(strcmp(instance.boards[i].name,targetName)==0)
        {
            break;
        }
    }

    if (instance.boards == NULL || (i == instance.numberOfBoards)) {
        printf("Could not find board\n");
        return;
    }

    cardNode* currNode = instance.selectedBoard->baseNode;
    while (currNode != NULL) {
        cardDelete(currNode->card->cardID);
    }

    for(i;i<instance.numberOfBoards-1;i++)
    {
        instance.boards[i]=instance.boards[i+1];
    }
    instance.numberOfBoards--;
    Board* ptr = instance.boards;
    if (instance.numberOfBoards == 0) {
        free(instance.boards);
        instance.boards = NULL;
    } else {
        Board *newPtr = (Board *) realloc(ptr, instance.numberOfBoards * sizeof(Board));
        if (newPtr == NULL) {
            printf("Could not realloc board array");
        }
        instance.boards = newPtr;
    }
    instance.selectedBoard = NULL;
    printf("Deleted board\n");
}

void sortCardsStatusDate()
{
    printf("Sorting cards in selected board");
    Board* board = instance.selectedBoard;
    Card *auxC;
    for(int i=0;i<board->numberOfCards-1;i++) {
        if (board->baseNode->card->status==DONE)
        {
            auxC=board->baseNode->card;
            board->baseNode->card=board->baseNode->next->card;
            board->baseNode->next->card=auxC;
        }
    }
    printf(".");

    for(int i=0;i<board->numberOfCards-1;i++) {
        if (board->baseNode->card->status==WORKING && board->baseNode->next->card->status!=DONE)
        {
            auxC=board->baseNode->card;
            board->baseNode->card=board->baseNode->next->card;
            board->baseNode->next->card=auxC;
        }
    }
    printf(".");

    while(1) {
        int cserelodott=0;
        for (int i = 0; i < board->numberOfCards - 1; i++) {
            if (board->baseNode->card->status == board->baseNode->next->card->status) {
                if (board->baseNode->card->timestamp < board->baseNode->next->card->timestamp) {
                    auxC = board->baseNode->card;
                    board->baseNode->card = board->baseNode->next->card;
                    board->baseNode->next->card = auxC;
                    cserelodott=1;
                }
            }
        }
        if(!cserelodott)break;
    }
    printf(" done\n");
}

void boardList()
{
    if(instance.numberOfBoards == 0) {
        printf("No boards\n");
        return;
    }

    for(int i=0; i<instance.numberOfBoards;i++)
    {
        printf("%s", instance.boards[i].name);
        if (strcmp(instance.selectedBoard->name, instance.boards[i].name) == 0) {
            printf(" (Selected)\n");
        } else {
            printf("\n");
        }
    }
}

int boardContainsUser(char* email)
{
    for(int i=0; i<instance.selectedBoard->numberOfUsers;i++) {
        if(strcmp(instance.selectedBoard->users[i], email)==0)return 1;
    }
    return 0;
}

void boardAddUser(char* email)
{
    if(boardContainsUser(email))
    {
        printf("\nBoard already contains user\n");
        return;
    }
    int i = 0;
    for (i = 0; i < instance.numberOfUsers; ++i) {
        if (strcmp(instance.users[i].email, email) == 0) {
            break;
        }
    }
    if (i == instance.numberOfUsers) {
        printf("User does not exist\n");
        return;
    }

    instance.selectedBoard->numberOfUsers++;
    char** auxArr;
    char** Arr=instance.selectedBoard->users;
    auxArr=(char**)realloc(Arr,instance.selectedBoard->numberOfUsers*sizeof(char*));
    instance.selectedBoard->users=auxArr;
    instance.selectedBoard->users[instance.selectedBoard->numberOfUsers-1]=email;
    printf("Added user to board\n");
}

void boardListUsers() {
    if (instance.selectedBoard->numberOfUsers == 0) {
        printf("No users added to this board\n");
        return;
    } else {
        for (int i = 0; i < instance.selectedBoard->numberOfUsers; i++) {
            printf("%s\n", instance.selectedBoard->users[i]);
        }
    }
}

void boardRemoveUser(char* email)
{
    if(!boardContainsUser(email))
    {
        printf("\nBoard doesn't contain user\n");
        return;
    }
    int i;
    for(i=0; i<instance.selectedBoard->numberOfUsers;i++) {
        if(strcmp(instance.selectedBoard->users[i], email)==0)
        {
            break;
        }
    }
    for(i;i<instance.selectedBoard->numberOfUsers-1;i++)
    {
        instance.selectedBoard->users[i]=instance.selectedBoard->users[i+1];
    }

    instance.selectedBoard->numberOfUsers--;
    char** auxArr;
    char** Arr=instance.selectedBoard->users;
    auxArr=(char**)realloc(Arr,instance.selectedBoard->numberOfUsers*sizeof(char*));
    instance.selectedBoard->users=auxArr;\

    printf("Removed user from board\n");
}



