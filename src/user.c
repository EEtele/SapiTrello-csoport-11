#include "../include/user.h"

User* userCreate(char* userName, char* userEmail) {
    User* user = calloc(1, sizeof(User));
    strcpy(user->name, userName);
    strcpy(user->email, userEmail);

    return user;
}

void userDelete(char* userEmail) {
    /*
    for (int i = 0; i < instance.numberOfBoards; i++) {
        if (boardContainsUser(instance.boards[i].name, userEmail)) {
            boardRemoveUser(instance.boards[i].name, userEmail);
        }
    }
    */

    for (int i = 0; i < instance.numberOfUsers; i++) {
        if (strcmp(instance.users[i].email, userEmail) == 0) {
            User* temp = &instance.users[i];

            for (int j = i; j < instance.numberOfUsers-1; j++) {
                instance.users[i] = instance.users[i+1];
            }

            instance.numberOfUsers--;
            instance.users = (User*)realloc(instance.users,
                                            instance.numberOfUsers*sizeof(User));

            free(temp);
            return;
        }
    }
}