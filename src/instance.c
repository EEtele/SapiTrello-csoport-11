#include "../include/instance.h"

void initializeDataFiles() {
    FILE* fout = fopen("data/boards.dat", "wb");
    fprintf(fout, "0");
    fclose(fout);

    fout = fopen("data/users.dat", "wb");
    fprintf(fout, "0");
    fclose(fout);

}
void initializeDir() {
    struct stat st = {0};

    if (stat("data", &st) == -1) {
        mkdir("data");
        printf("Created data directory\n");

        initializeDataFiles();
    }
}
int instanceLoad() {
    // Loads all boards and users from disk
    // Creates folders if empty

    instance.selectedBoard = NULL;
    instance.numberOfBoards = 0;
    instance.boards = NULL;
    instance.numberOfUsers = 0;
    instance.users = NULL;

    initializeDir();

    printf("Loading");

    FILE* fin = fopen("data/boards.dat", "rb");
    if (fin == NULL) {
        printf("Could not open boards file");
    }
    fscanf(fin, "%d\n", &instance.numberOfBoards);
    instance.boards = (Board*)calloc(instance.numberOfBoards, sizeof(Board));
    printf(".");
    // read boards from file
    for (int i = 0; i < instance.numberOfBoards; i++) {
        Board* currBoard = &instance.boards[i];
        // read board from file
        fread(currBoard, sizeof(Board), 1, fin);
        currBoard->baseNode = NULL;

        // create card array to convert to linked list
        Card* temp = (Card*)calloc(currBoard->numberOfCards, sizeof(Card));

        // read cards from file
        for (int j = 0; j < currBoard->numberOfCards; j++) {
            // read card from file
            fread(&temp[j], sizeof(Card), 1, fin);
            // read userlogs from file
            temp[j].userLog = (char**)calloc(temp[j].numberOfUserLog, sizeof(char*));
            for (int k = 0; k < temp[j].numberOfUserLog; k++) {
                temp[j].userLog[k] = (char*)calloc(MAX_USER_EMAIL_LENGTH, sizeof(char));
                // read userlog from file
                fread(temp[j].userLog[k], sizeof(char), MAX_USER_EMAIL_LENGTH, fin);
            }
        }

        instance.selectedBoard = currBoard;
        cardNode *currNode = NULL;
        for (int j = 0; j < currBoard->numberOfCards; j++) {
            cardNode* node = (cardNode *) calloc(1, sizeof(cardNode));
            if (node == NULL) {
                printf("Could not allocate node\n");
            }
            node->card = &temp[j];
            node->next = NULL;

            if (currNode == NULL) {
                currNode = node;
                currBoard->baseNode = node;
            } else {
                currNode->next = node;
                currNode = currNode->next;
            }
        }
        instance.selectedBoard = NULL;

        // read board users from file
        currBoard->users = (char**)calloc(currBoard->numberOfUsers, sizeof(char*));
        for (int j = 0; j < currBoard->numberOfUsers; j++) {
            currBoard->users[j] = (char*)calloc(MAX_USER_EMAIL_LENGTH, sizeof(char));
            // read board user from file
            fread(currBoard->users[j], sizeof(char), MAX_USER_EMAIL_LENGTH, fin);
        }
    }
    fclose(fin);
    printf(".");

    fin = fopen("data/users.dat", "rb");
    if (fin == NULL) {
        printf("Could not open users file");
    }
    fscanf(fin, "%d\n", &instance.numberOfUsers);
    instance.users = (User*)calloc(instance.numberOfUsers, sizeof(User));
    for (int i = 0; i < instance.numberOfUsers; i++) {
        fread(instance.users, sizeof(User), instance.numberOfUsers, fin);
    }
    fclose(fin);

    printf(".\n");
    printf("%d boards loaded. %d users loaded.\n", instance.numberOfBoards, instance.numberOfUsers);

    return 1;
}

int instanceWrite() {
    // Writes all boards and users to disk

    printf("Writing to file");

    FILE* fout = fopen("data/boards.dat", "wb");
    if (fout == NULL) {
        printf("Could not open boards file");
    }
    fprintf(fout, "%d\n", instance.numberOfBoards);
    printf(".");
    // write boards to file
    for (int i = 0; i < instance.numberOfBoards; i++) {
        Board* currBoard = &instance.boards[i];
        // write board to file
        fwrite(currBoard, sizeof(Board), 1, fout);

        // create card array to write to file
        Card* temp = (Card*)calloc(currBoard->numberOfCards, sizeof(Card));
        instance.selectedBoard = currBoard;
        for (int j = 0; j < currBoard->numberOfCards; j++) {
            temp[j] = *cardGet(j);
        }
        instance.selectedBoard = NULL;

        // write cards to file
        for (int j = 0; j < currBoard->numberOfCards; j++) {
            // write card to file
            fwrite(&temp[j], sizeof(Card), 1, fout);
            // write userlogs to file
            for (int k = 0; k < temp[j].numberOfUserLog; k++) {
                // write userlog to file
                fwrite(temp[j].userLog[k], sizeof(char), MAX_USER_EMAIL_LENGTH, fout);
            }
            free(temp[j].userLog);
        }

        free(temp);
        cardNode* node = currBoard->baseNode;
        while (node != NULL) {
            cardNode* aux = node;
            node = node->next;
            free(aux);
        }

        // write board users to file
        for (int j = 0; j < currBoard->numberOfUsers; j++) {
            // write board user to file
            fwrite(currBoard->users[j], sizeof(char), MAX_USER_EMAIL_LENGTH, fout);
        }

        free(currBoard->users);
    }
    free(instance.boards);
    fclose(fout);
    printf(".");

    fout = fopen("data/users.dat", "wb");
    if (fout == NULL) {
        printf("Could not open users file");
    }
    fprintf(fout, "%d\n", instance.numberOfUsers);
    for (int i = 0; i < instance.numberOfUsers; i++) {
        fwrite(instance.users, sizeof(User), instance.numberOfUsers, fout);
    }
    free(instance.users);
    fclose(fout);

    printf(".\n");

    return 1;
}