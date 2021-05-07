#include <stdio.h>
#include "domain/card.c"
#include "board.c"
#include "utilities/reset-commands.c"

int main() {
    //pls write file path for Card.txt in line below between the "", and remove the // from it.
    char deckSaveFilePath[100] = "\\Users\\steve\\CLionProjects\\machine-project-2\\Card.txt";

    int startUpPhase = 1;
    int gameStarted = 0;

    char lastCommand[100] = " ";
    char message[50] = " ";

    char firstCommand[50];
    char secondCommand[100];


    // Print default empty board
    printBoard(message);

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
            printHiddenBoard(message);
            resetCommands(firstCommand, secondCommand);
        }

            // SAVE TO FILE
        else if (strcmp(firstCommand, "SD") == 0) {
            // If file is included
            if (secondCommand[0] == '\0') {
                // Save to deck function...
                SaveDeckOfCards(deckSaveFilePath, message);
            } else {
                SaveDeckOfCards(secondCommand, message);
            }
        }


            // SHOW DECK OF CARDS (SW)
        else if (strcmp(firstCommand, "SW") == 0) {
            showAllCards();
            printBoard(message);
        }
            // SPLIT DECK OF CARDS (SPLIT <number>)
        else if (strcmp(firstCommand, "SI") == 0) {
            if (head == NULL) {
                strcpy(message, "Error! The deck is empty");
                printBoard(message);
            } else if (secondCommand[0] == '\0') {

                int cardPosition = rand() % 52;
                splitShuffleDeck(cardPosition, message);
            } else {
                int cardPosition = atoi(secondCommand);
                if (cardPosition > 1 && cardPosition < 52) {
                    splitShuffleDeck(cardPosition, message);

                } else {
                    strcpy(message, "Error: CardPosition not valid");
                    printBoard(message);
                }
            }
        } else if (strcmp(firstCommand, "SR") == 0) {
            if (head == NULL) {
                strcpy(message, "Error! The deck is empty");
                printBoard(message);
            } else {
                shuffleDeck(message);
                printBoard(message);
            }
        }

            // QUIT PROGRAM (QQ)
        else if (strcmp(firstCommand, "QQ") == 0) {
            break;
        }

            // START GAME (P)
        else if (strcmp(firstCommand, "P") == 0) {
            // No cards on board
            if (head == NULL) {
                // Print the empty board
                strcpy(message, "ERROR no cards");
            } else {
                strcpy(message, "GAME STARTED");
                gameStarted = 1;
                sortGameCards();
                printBoard(message);
            }
        } else {
            printBoard(message);
            strcpy(message, " ");
        }


        /** IN GAME PHASE **/

        while (gameStarted == 1) {

            printCommandBox(firstCommand, secondCommand, lastCommand, message);

            // QUIT CURRENT GAME AND RETURN TO START UP PHASE (Q)
            if (strcmp(firstCommand, "Q") == 0) {
                strcpy(message, "Returned to STARTUP PHASE");
                printBoard(message);
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
                strcpy(message, "Comman´d not available in the PLAY phase");
            } else {
                printBoard(message);
            }

//            // <Game Moves>
//            struct card *temphead = head;
//            int foundFirst = 0;
//            int foundSecond = 0;
//
//
//            //Goes through all cards and sees if their name is equals to the first command.
//            while(temphead!=NULL){
//                if(strcmp(temphead->name, firstCommand)==0 && temphead->visible == 1){
//                    foundFirst = 1;
//                }
//                if(strcmp(temphead->name, secondCommand)==0 && temphead->visible == 1){
//                    foundSecond = 1;
//                }
//                //Check if visible
//                if(foundFirst == 1 && foundSecond == 1){
//                    printf("Found Card\n");
//                    break;
//                }
//                temphead = temphead ->next;
//
//            }
//            if(foundFirst == 1 && foundSecond == 0){
//                printf("Card not found\n");
//            }


        }

    }

}



