#include "utilities/get-user-input.c"


void printHiddenBoard(char *message) {
    struct card *temporaryCard;
    temporaryCard = head;


    if (temporaryCard == NULL) {
        strcpy(message, "Error! The deck is empty");
        return;
    }

    int y = getHighestCardPosition();
    int fCount = 1;


    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\n");
    for (int i = 0; i <= y; ++i) {
        printf("\n");
        for (int j = 0; j <= 6; ++j) {
            if (temporaryCard == NULL) {
                printf(" ");
            } else {
                printf("%[]\t");
                temporaryCard = temporaryCard->next;
            }
        }

        if (i % 2 == 0) {
            printf("\t\t[]\tF%d", fCount);
            fCount = fCount + 1;
        }
    }
    strcpy(message, "OK");
    printf("\n\n");
}

void printBoard(char *message) {
    struct card *current = head;
    int count = 0;

    if (current == NULL) {
        strcpy(message, "Error! The deck is empty");
        return;
    }

    int y = getHighestCardPosition();
    int fCount = 1;


    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\n");
    for (int i = 0; i <= y; ++i) {

        printf("\n");

        for (int j = 0; j <= 6; ++j) {

            int found = 0;

            // for loop der looper igennem linked list
            while (current != NULL) {

                if (current->x == j && current->y == i) {
                    found = 1;
                    if (current->visible == 1) {
                        printf("%s\t", current->name);
                    } else {
                        printf("[]\t");
                    }
                    count = count + 1;
                    current = head;
                    break;
                } else {
                    current = current->next;
                }
            }

            if (found == 0) {
                printf("\t");
                current = head;
            }
        }

        if (i % 2 == 0 && fCount < 5) {
            printf("\t\t[]\tF%d", fCount);
            fCount = fCount + 1;
        }
    }
    strcpy(message, "OK");

    printf("\n\n");
};

void printCommandBox(char *firstCommand, char *secondCommand, char *lastCommand, char message[]) {


    printf("LAST Command: %s", lastCommand);
    printf("\n");
    printf("Message: %s", message);
    printf("\n");
    printf("INPUT > ");
    getUserInput(firstCommand, secondCommand, lastCommand);
    printf("\n");
}