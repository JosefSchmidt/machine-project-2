#include <stdio.h>
#include "domain/card.c"
#include "board.c"


int main() {

    int startUpPhase = 1;
    int gameStarted = 0;

    char lastCommand[50] = " ";
    char message[] = " ";
    char * pMessage = message;

    char firstCommand[50];
    char secondCommand[50];

    // Print default empty board
    printEmptyBoard();

    while (startUpPhase == 1) {
        printCommandBox(firstCommand, secondCommand, lastCommand, message);


        /** START UP PHASE **/

        // LOAD FILE - File not specified
//        if (strcmp(firstCommand, "LD") == 0) {
//            createDefaultCardList();
//        }

        // QUIT PROGRAM (QQ)
        if (strcmp(firstCommand, "QQ") == 0) {
            startUpPhase = 0;
            break;
        }

        // START GAME (P)
        if (strcmp(firstCommand, "P") == 0) {
            printf("GAME STARTED");
            gameStarted = 1;
        }

        // Print the empty board
        printEmptyBoard();

        /** IN GAME PHASE **/

        while (gameStarted == 1) {

            printCommandBox(firstCommand, secondCommand, lastCommand, message);

            // QUIT CURRENT GAME AND RETURN TO START UP PHASE (Q)
            if (strcmp(firstCommand, "Q") == 0) {
                gameStarted = 0;
            }


            // QUIT PROGRAM (QQ)
            if (strcmp(firstCommand, "QQ") == 0) {
                gameStarted = 0;
                startUpPhase = 0;
                break;
            }

            if (
                    strcmp(firstCommand, "LD") == 0 ||
                    strcmp(firstCommand, "SW") == 0 ||
                    strcmp(firstCommand, "SI") == 0 ||
                    strcmp(firstCommand, "SE") == 0 ||
                    strcmp(firstCommand, "SD") == 0
                    ) {
                strcpy(pMessage, "Command not available in the PLAY phase");

            }

        }

    }
    
//    createDefaultCardList();
//    displayCardListFromFirst();
}



