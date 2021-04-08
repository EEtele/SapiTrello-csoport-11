#ifndef SAPITRELLO_CSOPORT_11_USER_H
#define SAPITRELLO_CSOPORT_11_USER_H

#include <string.h>

#include "board.h"
#include "instance.h"

typedef struct User {
    char name[MAX_USER_NAME_LENGTH];
    char email[MAX_USER_EMAIL_LENGTH];
} User;

#endif //SAPITRELLO_CSOPORT_11_USER_H
