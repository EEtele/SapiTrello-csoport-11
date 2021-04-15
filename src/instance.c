#include "../include/instance.h"

void initializeDataFiles() {
    FILE* fout = fopen("data/boards.dat", "wt");
    fprintf(fout, "0");
    fclose(fout);

    fout = fopen("data/users.dat", "wt");
    fprintf(fout, "0");
    fclose(fout);

}
int initializeDir() {
    struct stat st = {0};

    if (stat("data", &st) == -1) {
        mkdir("data");

        initializeDataFiles();

        return 1;
    } else {
        printf("dir already exists\n");

        initializeDataFiles();

        return 0;
    }
}
int instanceLoad() {
    // Loads all boards and users from disk
    // Creates folders if empty

    instance.selectedBoard = NULL;

    initializeDir();

    FILE* fin = fopen("data/boards.dat", "rt");
    fscanf(fin, "%i", &instance.numberOfBoards);
    instance.boards = (Board*)calloc(instance.numberOfBoards, sizeof(Board));
    for (int i = 0; i < instance.numberOfBoards; i++) {
        Board* board = (Board*)calloc(1, sizeof(Board));

        fscanf(fin, "%[^\n]\n", board->name);

        char path[MAX_BOARD_NAME_LENGTH+15] = "data/";
        strcat(path, board->name);

        FILE* boardFin = fopen(path, "rt");
        fread(&instance.boards[i], sizeof(instance.boards[i]), 1, boardFin);
        fclose(boardFin);
    }
    fclose(fin);

    fin = fopen("data/users.dat", "rt");
    fscanf(fin, "%i", &instance.numberOfUsers);
    instance.users = (User*)calloc(instance.numberOfUsers, sizeof(User));
    for (int i = 0; i < instance.numberOfUsers; i++) {
        fscanf(fin, "%[^\n]\n", instance.users[i].name);
        fscanf(fin, "%[^\n]\n", instance.users[i].email);
    }
    fclose(fin);

    return 1;
}

int instanceWrite() {
    // Writes all boards and users to disk

    FILE* fout = fopen("data/boards.dat", "wt");

    struct stat st = {0};
    //for some reason this doesnt print anything to the file
    fprintf(fout, "%i\n", instance.numberOfBoards);
    for (int i = 0; instance.numberOfBoards; i++) {
        fprintf(fout, "%s\n", instance.boards[i].name);

        char dirPath[MAX_BOARD_NAME_LENGTH+15] = "data/";
        strcat(dirPath, instance.boards[i].name);
        if (stat(dirPath, &st) == -1) {
            mkdir(dirPath);
        }

        char filePath[MAX_BOARD_NAME_LENGTH+15] = "../";
        strcat(filePath, dirPath);
        strcat(filePath, "/Board.dat");

        FILE* boardFout = fopen(filePath, "wt");
        //filePath looks fine, but fopen cannot open it :L
        fwrite(&instance.boards[i], sizeof(instance.boards[i]), 1, boardFout);
        fclose(boardFout);
    }
    fclose(fout);

    fout = fopen("data/users.dat", "wt");
    fprintf(fout, "%i\n", instance.numberOfUsers);
    for (int i = 0; i < instance.numberOfUsers; i++) {
        fprintf(fout, "%s\n", instance.users[i].name);
        fprintf(fout, "%s\n", instance.users[i].email);
    }
    fclose(fout);

    return 1;
}