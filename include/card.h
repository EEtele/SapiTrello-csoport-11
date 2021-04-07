#ifndef SAPITRELLO_CSOPORT_11_CARD_H
#define SAPITRELLO_CSOPORT_11_CARD_H

typedef enum {
    TODO, WORKING, DONE;
} Status;

typedef struct {
    int cardID;

    char* title;
    char* description;
    time_t timestamp;
    Status status;
    char* user;
    char** userLog;
} Card;

#endif //SAPITRELLO_CSOPORT_11_CARD_H
