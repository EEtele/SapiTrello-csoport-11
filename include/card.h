#ifndef SAPITRELLO_CSOPORT_11_CARD_H
#define SAPITRELLO_CSOPORT_11_CARD_H

typedef struct {
    char* name;
    char* email;
} User;

enum Status {
    TODO, WORKING, DONE
};

typedef struct Card {
    int cardID;	// generate using rand()
    //		(NOTE: will have to verify availability of generated ID)

    char* title;
    char* description;
//    time_t timestamp;	//	Date when card was created
    enum Status status;
    char* user;	// Assigned user (store email); board must contain this user
    char** userLog;	// Store emails of all users who worked on this card
    int userLogCounter; //hany email van a userLogban
} Card;

Card cardCreate(char * cardName, char * cardDescription, char * user);
void cardModifyUser(Card * card, char * user);
void cardDelete(Card * card);
char * cardAssignUser(Card * card);
//void cardRemoveUser(int cardID, char *userEmail);
enum Status cardGetStatus(Card * card);
//cardUpdate(int cardID);
void cardSetStatus(Card * card, enum Status status);
char ** cardGetUserLog(Card * card);

#endif //SAPITRELLO_CSOPORT_11_CARD_H
