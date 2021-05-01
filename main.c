#include <stdio.h>
#include "domain/card.c"
#include "board.c"
#include "utilities/reset-commands.c"

int main() {

    int startUpPhase = 1;
    int gameStarted = 0;

    char lastCommand[50] = " ";
    char message[50] = " ";

    char firstCommand[50];
    char secondCommand[50];


    // Print default empty board
    printEmptyBoard();

    while (startUpPhase == 1) {
        printCommandBox(firstCommand, secondCommand, lastCommand, message);



        /** START UP PHASE **/

        // LOAD FILE - File not specified
        if (strcmp(firstCommand, "LD") == 0) {
            // If file is included
            if (secondCommand[0] == '\0') {
                // If secondCommand is a valid file -> Create deck out of file content
                createDefaultCardList(message);
            } else {
                uploadDeckOfCards(secondCommand, message);
            }
            resetCommands(firstCommand, secondCommand);
        }

            // QUIT PROGRAM (QQ)
        else if (strcmp(firstCommand, "QQ") == 0) {
            break;
        }

            // START GAME (P)
        else if (strcmp(firstCommand, "P") == 0) {
            strcpy(message, "GAME STARTED");

            gameStarted = 1;
        } else {
            strcpy(message, " ");
        }

        // Print the empty board
        printEmptyBoard();

        /** IN GAME PHASE **/

        while (gameStarted == 1) {

            printCommandBox(firstCommand, secondCommand, lastCommand, message);

            // QUIT CURRENT GAME AND RETURN TO START UP PHASE (Q)
            if (strcmp(firstCommand, "Q") == 0) {
                strcpy(message, "Returned to STARTUP PHASE");

                gameStarted = 0;
            }


                // QUIT PROGRAM (QQ)
            else if (strcmp(firstCommand, "QQ") == 0) {
                gameStarted = 0;
                startUpPhase = 0;
                break;
            } else if (
                    strcmp(firstCommand, "LD") == 0 ||
                    strcmp(firstCommand, "SW") == 0 ||
                    strcmp(firstCommand, "SI") == 0 ||
                    strcmp(firstCommand, "SE") == 0 ||
                    strcmp(firstCommand, "SD") == 0
                    ) {
                strcpy(message, "Command not available in the PLAY phase");

            }

            // Print the empty board
            printEmptyBoard();
        }

    }

//    createDefaultCardList();
//    displayCardListFromFirst();
}



