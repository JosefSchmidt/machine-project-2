#include <stdio.h>
#include "domain/card.c"
#include "board.c"


int main() {

    int gameOn = 1;

    char lastCommand[50] = " ";

    char firstCommand[50];
    char secondCommand[50];


    while(gameOn == 1) {

        printEmptyBoard();
        printCommandBox(firstCommand, secondCommand, lastCommand);
    }


//    createDefaultCardList();
//    displayCardListFromFirst();
}


