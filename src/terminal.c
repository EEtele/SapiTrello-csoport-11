#include "../include/terminal.h"

/*
 command flags:
   -1 - exit
    0 - worked like a charm
    1 - syntax error
    2 - invalid number of parameters
    3 - invalid parameter
    4 - nothing selected
*/

// Only extracts from within " quotes
char** extractParameters(char* input, int* size) {
    char** paramList;
    int listSize = 0;

    char paramBuffer[PARAM_BUFFER_SIZE];
    int currPos = 0, bytes;
    while(currPos < strlen(input)) {
        sscanf(input + currPos, " \"%[^\"]%n", paramBuffer, &bytes);
        if (strcmp(paramBuffer, "") != 0) {
            if (listSize == 0) {
                listSize++;
                paramList = (char**)calloc(listSize, sizeof(char*));
            } else {
                listSize++;
                paramList = (char**)realloc(paramList, listSize*sizeof(char*));
            }
            paramList[listSize-1] = (char*)calloc(PARAM_BUFFER_SIZE, sizeof(char));
            strcpy(paramList[listSize-1], paramBuffer);
        } else {
            break;
        }
        currPos += bytes+2;     // offset
        paramBuffer[0] = '\0';  // clear buffer
    }

    (*size) = listSize;
    return paramList;
}
int input(char* buffer) {
    int flag = 0;
    char** parameterList;
    int listSize = 0;

    if (strcmp(buffer, "user") == 0) {
        scanf(" %s", buffer);
        if (strcmp(buffer, "new") == 0) {           // user new
            scanf(" %[^\n]", buffer);
            parameterList = extractParameters(buffer, &listSize);
            if (listSize == 2) {        // this command requires 2 parameters
                userCreate(parameterList[0], parameterList[1]);
            } else {
                flag = 2;
            }
        } else if (strcmp(buffer, "delete") == 0) { // user delete
            scanf(" %[^\n]", buffer);
            parameterList = extractParameters(buffer, &listSize);
            userDelete(parameterList[0]);
        } else if (strcmp(buffer, "list") == 0) {   // user list
            userList();
        } else {
            flag = 1;
        }
    } else if (strcmp(buffer, "board") == 0) {
        scanf(" %s", buffer);
        if (strcmp(buffer, "new") == 0) { // board new
            scanf(" %[^\n]", buffer);
            parameterList = extractParameters(buffer, &listSize);
            if(listSize==1) {
                boardCreate(parameterList[0]);
            }
            else flag=2;

        } else if (strcmp(buffer, "modify") == 0) { // board modify
            if (instance.selectedBoard == NULL) {
                flag = 4;
            } else {
                scanf(" %[^\n]", buffer);
                parameterList = extractParameters(buffer, &listSize);
                if (listSize == 1) {
                    boardModify(parameterList[0]);
                } else flag = 2;
            }

        } else if (strcmp(buffer, "remove") == 0) { // board remove
            if (instance.selectedBoard == NULL) {
                flag = 4;
            } else {
                scanf(" %[^\n]", buffer);
                parameterList = extractParameters(buffer, &listSize);
                if (listSize == 1) {
                    boardDelete(parameterList[0]);
                } else flag = 2;
            }

        } else if (strcmp(buffer, "list") == 0) {   // board list
                boardList();

        } else if (strcmp(buffer, "select") == 0) { // board select
            scanf(" %[^\n]", buffer);
            parameterList = extractParameters(buffer, &listSize);
            if (listSize == 1) {
                boardSelect(parameterList[0]);
            } else flag = 2;
        } else if (strcmp(buffer, "user") == 0) {
            scanf(" %s", buffer);
            if (instance.selectedBoard == NULL) {
                flag = 4;
            } else {
                if (strcmp(buffer, "add") == 0) {       // board user add
                    scanf(" %[^\n]", buffer);
                    parameterList = extractParameters(buffer, &listSize);
                    if (listSize == 1) {
                        boardAddUser(parameterList[0]);
                    } else flag = 2;
                } else if (strcmp(buffer, "list") == 0) {
                    boardListUsers();
                } else if (strcmp(buffer, "remove") == 0) { // board user remove
                    scanf(" %[^\n]", buffer);
                    parameterList = extractParameters(buffer, &listSize);
                    if (listSize == 1) {
                        boardRemoveUser(parameterList[0]);
                    } else flag = 2;
                } else {
                    flag = 1;
                }
            }
        } else {
            flag = 1;
        }
    } else if (strcmp(buffer, "card") == 0) {
        if (instance.selectedBoard == NULL) {
            flag = 4;
        } else {
            scanf(" %s", buffer);
            if (strcmp(buffer, "new") == 0) {           // card new
                scanf(" %[^\n]", buffer);
                parameterList = extractParameters(buffer, &listSize);
                if (listSize == 2) {
                    cardCreate(parameterList[0], parameterList[1]);
                } else {
                    flag = 2;
                }
            } else if (strcmp(buffer, "modify") == 0) {
                scanf(" %s", buffer);
                if (strcmp(buffer, "name") == 0) {      // card modify name
                    scanf(" %[^\n]", buffer);
                    parameterList = extractParameters(buffer, &listSize);
                    if (listSize == 2) {
                        // Convert string to number (if it fails, it wont change value of num)
                        int num = INT_MAX;
                        sscanf(parameterList[0], "%d", &num);

                        cardModifyName(num, parameterList[1]);
                    } else {
                        flag = 2;
                    }
                } else if (strcmp(buffer, "description") == 0) {    // card modify description
                    scanf(" %[^\n]", buffer);
                    parameterList = extractParameters(buffer, &listSize);
                    if (listSize == 2) {
                        int num = INT_MAX;
                        sscanf(parameterList[0], "%d", &num);

                        cardModifyDescription(num, parameterList[1]);
                    } else {
                        flag = 2;
                    }
                } else {
                    flag = 1;
                }
            } else if (strcmp(buffer, "remove") == 0) { // card remove
                scanf(" %[^\n]", buffer);
                int num = INT_MAX;
                sscanf(buffer, "%d", &num);
                if (num != INT_MAX) {
                    cardDelete(num);
                } else {
                    flag = 1;
                }
            } else if (strcmp(buffer, "list") == 0) {   // card list
                cardList();
            } else if (strcmp(buffer, "sort") == 0) {
                sortCardsStatusDate();
            } else if (strcmp(buffer, "user") == 0) {
                scanf(" %s", buffer);
                if (strcmp(buffer, "assign") == 0) {    // card user assign
                    scanf(" %[^\n]", buffer);
                    parameterList = extractParameters(buffer, &listSize);
                    if (listSize == 1) {
                        int num = INT_MAX;
                        sscanf(buffer, "%d", &num);

                        cardAssignUser(num, parameterList[0]);
                    } else {
                        flag = 2;
                    }
                } else if (strcmp(buffer, "remove") == 0) { // card user remove
                    scanf(" %[^\n]", buffer);
                    parameterList = extractParameters(buffer, &listSize);
                    if (listSize == 1) {
                        int num = INT_MAX;
                        sscanf(buffer, "%d", &num);

                        cardRemoveUser(num, parameterList[0]);
                    } else {
                        flag = 2;
                    }
                } else {
                    flag = 1;
                }
            } else if (strcmp(buffer, "status") == 0) { // card status
                scanf(" %[^\n]", buffer);
                int num = INT_MAX;
                sscanf(buffer, "%d\n", &num);
                if (num != INT_MAX) {
                    cardGetStatus(num);
                    printf("\n");
                } else {
                    flag = 2;
                }
            } else if (strcmp(buffer, "update") == 0) { // card update
                scanf(" %[^\n]", buffer);
                parameterList = extractParameters(buffer, &listSize);
                if (listSize == 1) {
                    int num = INT_MAX;
                    sscanf(parameterList[0], "%d", &num);

                    cardUpdate(num);
                } else if (listSize == 2) {
                    int num = INT_MAX;
                    sscanf(parameterList[0], "%d", &num);

                    enum Status stat;

                    if (strcmp(parameterList[1], "TODO") == 0) {
                        stat = TODO;
                    } else if (strcmp(parameterList[1], "WORKING") == 0) {
                        stat = WORKING;
                    } else if (strcmp(parameterList[1], "DONE") == 0) {
                        stat = DONE;
                    } else {
                        flag = 3;
                    }

                    if (flag != 3) {
                        cardSetStatus(num, stat);
                    }
                } else {
                    flag = 2;
                }
            } else if (strcmp(buffer, "log") == 0) {    // card log
                scanf(" %[^\n]", buffer);
                int num = INT_MAX;
                sscanf(buffer, "%d\n", &num);
                if (num != INT_MAX) {
                    cardGetUserLog(num);
                } else {
                    flag = 2;
                }
            } else {
                flag = 1;
            }
        }
    } else if (strcmp(buffer, "exit") == 0) {       // exit
        flag = -1;
    } else {
        flag = 1;
    }

    return flag;
}
void terminalLoop() {
    char* buffer = (char*)calloc(INPUT_BUFFER_SIZE, sizeof(char)); // buffer for input

    while (1) {
        printf(">");
        scanf(" %s", buffer);

        // Convert input to lowercase
        for (int i = 0; i < buffer[i]; i++) {
            buffer[i] = (char)tolower(buffer[i]);
        }

        int commandFlag = input(buffer);

        switch (commandFlag) {
            case -1: printf("Exiting..\n"); return;
            case 0: break;
            case 1: printf("Syntax error\n"); break;
            case 2: printf("Invalid number of parameters\n"); break;
            case 3: printf("Invalid parameter\n"); break;
            case 4: printf("Nothing selected\n"); break;
            default: printf("ERROR: Unknown command flag %i\n", commandFlag);
        }

        if (commandFlag > 0) {
            if (buffer[strlen(buffer)-1] != '\"') {
                scanf(" %[^\n]\n", buffer);   // If theres an error, clear input
            }
        }
    }
}