#include "utilities/get-user-input.c"


void printEmptyBoard() {
    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\n");
    printf("\n");


    for (int j = 0; j < 9; ++j) {
        if(j < 1) printf(" \t \t \t \t \t \t \t\t \tF1\n");
        if(j < 4)
            printf(" \t \t \t \t \t \t \t\t \tF1\n");
    }

}

void printBoard() {
    for (int j = 0; j < 9; ++j) {
        if(j < 1) printf("[]\t[]\t[]\t[]\t[]\t[]\t[]\t\t[]\tF1\n");
        if(j < 4)
            printf(" \t[]\t[]\t[]\t[]\t[]\t[]\t\t[]\tF1\n");
    }
};

void printCommandBox(char * firstCommand, char * secondCommand, char * lastCommand) {

    printf("LAST Command: %s", lastCommand);
    printf("\n");
    printf("Message: ");
    printf("\n");
    printf("INPUT > ");
    getUserInput(firstCommand, secondCommand, lastCommand);
    printf("\n");
}