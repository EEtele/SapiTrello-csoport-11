#include "../include/board.h"

void boardCreate(char* boardName)
{
    Board* tempB=(Board*)calloc(1,sizeof(Board));
    strcpy((*tempB).name, boardName);
    if (instance.boards == NULL) {
        instance.boards = (Board*)calloc(1, sizeof(Board));
        instance.boards[0] = *tempB;
        instance.numberOfBoards=1;

    } else {
        Board* ptr = instance.boards;
        int n = instance.numberOfBoards;
        Board* newPtr = (Board*)realloc(ptr, (n+1)*sizeof(Board));
        instance.boards = newPtr;
        instance.boards[n] = *tempB;
        instance.numberOfBoards++;
    }
}

void sortCardsStatusDate(Board board)
{

}

void sortBoards();

/*Board modifyBoard(int select, string newSring, int newNum)
{
    //1
}*/

