#include <stdio.h>
#include <stdlib.h>
#include "../include/board.h"



/*
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

*/




void boardCreate(char* boardName)
{
    Board* tempB=(Board*)calloc(1,sizeof(Board));
    strcpy((*tempB).name, boardName);
    if (instance.boards == NULL) {
        instance.boards = (Board*)calloc(1, sizeof(Board));
        instance.boards[0] = tempB;
        instance.numberOfBoards=1;

    } else {
        Board* ptr = instance.boards;
        int n = instance.numberOfBoards;
        Board* newPtr = (Board*)realloc(ptr, (n+1)*sizeof(Board));
        instance.boards = newPtr;
        instance.boards[n] = tempB;
        instance.numberOfBoards++;
    }
}

/*void boardAddCard(Card card,Board Board){
    if(Board.baseNode=NULL)
    {
        cardNode* temp=(cardNode*)malloc(sizeof(cardNode));
        (*temp).card=card;
        (*temp).next=NULL;
        Board.baseNode=temp;
        return;
    }
    cardNode* currNode;
    currNode=Board.baseNode;
    while(currNode->next!=NULL)
    {
        currNode=currNode->next;
    }


}*/

void sortCardsStatusDate(Board board)
{

}

void sortBoards();

/*Board modifyBoard(int select, string newSring, int newNum)
{
    //1
}*/

