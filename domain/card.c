#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Function declarations
char getDeckType(int type);

char getDeckValue(int value);

int getHighestCardPosition();

void deleteCardList();

void printEmptyBoard();

void printHiddenBoard();

struct card {
    char name[3];
    int x;
    int y;
    struct card *next;
    struct card *previous;
} *head, *last;


void createDefaultCardList(char *message) {
    struct card *newCard;
    int headerHasBeenSet = 0;

    head = (struct card *) malloc(sizeof(struct card));

    if (head == NULL) {
        strcpy(message, "Error! Unable to allocate memory");
        printEmptyBoard();
        return;
    } else {
        int y = 0;
        int x = 0;

        // Card type
        for (int i = 1; i <= 4; i++) {
            char cardType = getDeckType(i);

            // Card number
            for (int j = 1; j <= 13; ++j) {
                char cardValue = getDeckValue(j);

                // Create the card name (String)
                char name[] = {cardValue, cardType, '\0'};


                if (headerHasBeenSet == 0) {
                    strcpy(head->name, name);
                    head->previous = NULL;
                    head->next = NULL;
                    head->x = x;
                    head->y = y;
                    headerHasBeenSet = 1;
                    last = head;
                } else {
                    newCard = (struct card *) malloc(sizeof(struct card));
                    strcpy(newCard->name, name);
                    newCard->previous = head;
                    newCard->next = NULL;
                    newCard->x = x;
                    newCard->y = y;

                    last->next = newCard;
                    last = newCard;
                }

                if (x == 6) {
                    x = 0;
                    y = y + 1;
                } else {
                    x = x + 1;
                }
            }
        }

        strcpy(message, "OK");
        printHiddenBoard();
    }
}

void uploadDeckOfCards(char filePath[], char *message) {

    // "/Users/josefschmidt/Desktop/machine-project-2/my_file.txt"
    FILE *in_file = fopen(filePath, "r");

    // test for files not existing.
    if (in_file == NULL) {
        deleteCardList();
        strcpy(message, "Error! File could not be found");
        printEmptyBoard();
        return;
    }

    // Delete the current card list
    deleteCardList();

    struct card *newCard;
    int headerHasBeenSet = 0;
    head = (struct card *) malloc(sizeof(struct card));
    int cardCount = 0;

    if (head == NULL) {
        strcpy(message, "Error! Unable to allocate memory");
        printEmptyBoard();
        return;
    }
    int y = 0;
    int x = 0;

    char line[3];

    // Load in the cards from file and validate cards
    while (fscanf(in_file, "%s", line) != EOF) {

        if (headerHasBeenSet == 0) {
            printf("%s X: %d, Y: %d \n", line, x, y);
            strcpy(head->name, line);
            head->previous = NULL;
            head->next = NULL;
            head->x = x;
            head->y = y;
            headerHasBeenSet = 1;
            last = head;
        } else {
            printf("%s X: %d, Y: %d \n", line, x, y);
            newCard = (struct card *) malloc(sizeof(struct card));
            strcpy(newCard->name, line);
            newCard->previous = head;
            newCard->next = NULL;
            newCard->x = x;
            newCard->y = y;

            last->next = newCard;
            last = newCard;
        }

        cardCount = cardCount + 1;

        if (x < 6) {
            x = x + 1;
        } else {
            x = 0;
            y = y + 1;
        }
    }


    fclose(in_file);

    strcpy(message, "Uploaded cards from file");
    printHiddenBoard();
}

void displayCardListFromFirst() {

    int y = getHighestCardPosition();

    for (int i = 0; i < y; ++i) {
        for (int j = 0; j < 7; ++j) {

        }
    }

    struct card *temporaryCard;


    if (head == NULL) {
        printf("The deck is empty");
    } else {
        temporaryCard = head;
        printf("The cards are: \n");

        while (temporaryCard != NULL) {
            printf("%s\n", temporaryCard->name);
            temporaryCard = temporaryCard->next;
        }
    }
}


char getDeckType(int type) {
    switch (type) {
        // Clubs
        case 1:
            return 'C';
            // Diamonds
        case 2:
            return 'D';
            // Hearts
        case 3:
            return 'H';
            // Spades
        case 4:
            return 'S';
        default:
            return 'x';
    }
}

char getDeckValue(int value) {
    if (value == 0 || value > 13) {
        printf("Could not find the correct value by input. Please input a different value");
        return '0';
    } else if (value == 10) {
        return 'T';
    } else if (value == 11) {
        return 'J';
    } else if (value == 12) {
        return 'Q';
    } else if (value == 13) {
        return 'K';
    } else if (value == 1) {
        return 'A';
    } else {
        return value + '0';
    }
}

int getHighestCardPosition() {
    int currentLargestY = 0;
    struct card *current = head;

    while (current != NULL) {
        if (current->previous == NULL) {
            currentLargestY = current->y;
        } else {
            if (currentLargestY < current->y) {
                currentLargestY = current->y;
            }
        }
        current = current->next;
    }

    return currentLargestY;
}

void deleteCardList() {
    struct card *current = head;
    struct card *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    head = NULL;
}

