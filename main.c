#include <stdio.h>
#include "domain/card.c"
#include "board.c"

int main() {

    int startUpPhase = 1;
    int gameStarted = 0;

    char lastCommand[50] = " ";
    char message[50] = " ";
    
    char firstCommand[50];
    char secondCommand[50];

    FILE *in_file = fopen("/Users/josefschmidt/Desktop/machine-project-2/my_file.txt", "r");

    // test for files not existing.
    if (in_file == NULL) {
        printf("Error! Could not open file\n");
        exit(-1); // must include stdlib.h
    }

    char int_var_1[100];

    while (fgets(int_var_1, 100, in_file) != NULL) {
        printf("%s", int_var_1);
    }
    fclose(in_file);
    return 0;

//    // Print default empty board
//    printEmptyBoard();
//
//    while (startUpPhase == 1) {
//        printCommandBox(firstCommand, secondCommand, lastCommand, message);
//
//
//
//        /** START UP PHASE **/
//
//        // LOAD FILE - File not specified
//        if (strcmp(firstCommand, "LD") == 0) {
//
//
//
//            // If secondCommand is a valid file -> Create deck out of file content
//            if() {
//
//            } else {
//            // else create default deck
//            createDefaultCardList();
//
//            }
//
//        }
//
//        // QUIT PROGRAM (QQ)
//        if (strcmp(firstCommand, "QQ") == 0) {
//            startUpPhase = 0;
//            break;
//        }
//
//        // START GAME (P)
//        if (strcmp(firstCommand, "P") == 0) {
//            strcpy(message, "GAME STARTED");
//
//            gameStarted = 1;
//        }
//
//        // Print the empty board
//        printEmptyBoard();
//
//        /** IN GAME PHASE **/
//
//        while (gameStarted == 1) {
//
//            printCommandBox(firstCommand, secondCommand, lastCommand, message);
//
//            // QUIT CURRENT GAME AND RETURN TO START UP PHASE (Q)
//            if (strcmp(firstCommand, "Q") == 0) {
//                strcpy(message, "Returned to STARTUP PHASE");
//
//                gameStarted = 0;
//            }
//
//
//            // QUIT PROGRAM (QQ)
//            if (strcmp(firstCommand, "QQ") == 0) {
//                gameStarted = 0;
//                startUpPhase = 0;
//                break;
//            }
//
//            if (
//                    strcmp(firstCommand, "LD") == 0 ||
//                    strcmp(firstCommand, "SW") == 0 ||
//                    strcmp(firstCommand, "SI") == 0 ||
//                    strcmp(firstCommand, "SE") == 0 ||
//                    strcmp(firstCommand, "SD") == 0
//                    ) {
//                strcpy(message, "Command not available in the PLAY phase");
//
//            }
//
//            // Print the empty board
//            printEmptyBoard();
//        }
//
//    }

//    createDefaultCardList();
//    displayCardListFromFirst();
}



