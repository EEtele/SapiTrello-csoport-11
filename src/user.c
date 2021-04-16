#include "../include/user.h"

void userCreate(char* userName, char* userEmail) {
    struct User* user = (User*)calloc(1, sizeof(User));
    strcpy(user->name, userName);
    strcpy(user->email, userEmail);

    if (instance.users == NULL) {
        instance.users = (User*)calloc(1, sizeof(User));
        instance.numberOfUsers = 1;
    } else {
        instance.numberOfUsers++;
        instance.users = (User*)realloc(instance.users, instance.numberOfUsers*sizeof(User));
    }
    instance.users[instance.numberOfUsers-1] = *user;
    free(user);

    printf("Successfully created user %s\n", userEmail);
}

void userDelete(char* userEmail) {

    for (int i = 0; i < instance.numberOfBoards; i++) {
        if (boardContainsUser(userEmail)) {
            boardRemoveUser(userEmail);
        }
    }

    for (int i = 0; i < instance.numberOfUsers; i++) {
        if (strcmp(instance.users[i].email, userEmail) == 0) {
            instance.numberOfUsers--;
            if (instance.numberOfUsers == 0) {
                free(instance.users);
                instance.users = NULL;
            } else {
                for (int j = i; j < instance.numberOfUsers - 1; j++) {
                    instance.users[i] = instance.users[i + 1];
                }
                instance.users = (User*)realloc(instance.users,
                                                  instance.numberOfUsers * sizeof(User));
            }

            printf("Successfully deleted user %s\n", userEmail);
            return;
        }
    }

    printf("Could not find user\n");
}

void userList() {
    if (instance.numberOfUsers == 0) {
        printf("There are no users\n");
    } else {
        for (int i = 0; i < instance.numberOfUsers; i++) {
            printf("%s (%s)\n", instance.users[i].name,
                   instance.users[i].email);
        }
    }
}