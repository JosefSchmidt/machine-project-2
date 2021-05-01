#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function declarations
char getDeckType(int type);

char getDeckValue(int value);

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
        printf("Unable to allocate memory");
    } else {
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
                    headerHasBeenSet = 1;
                    last = head;
                } else {
                    newCard = (struct card *) malloc(sizeof(struct card));
                    strcpy(newCard->name, name);
                    newCard->previous = head;
                    newCard->next = NULL;

                    last->next = newCard;
                    last = newCard;
                }
            }
        }

        strcpy(message, "OK");
    }
}

void uploadDeckOfCards(char filePath[], char *message) {

    // "/Users/josefschmidt/Desktop/machine-project-2/my_file.txt"
    FILE *in_file = fopen(filePath, "r");

    // test for files not existing.
    if (in_file == NULL) {
        strcpy(message, "Error! File could not be found");
        return;
    }

    char int_var_1[2000];


    // Load in the cards from file and validate cards
    while (fgets(int_var_1, 2000, in_file) != NULL) {
        printf("%s", int_var_1);
    }
    fclose(in_file);


    strcpy(message, "Uploaded cards from file");
}

void displayCardListFromFirst() {
    struct card *temporaryCard;

    if (head == NULL) {
        printf("The deck is empty");
    } else {
        temporaryCard = head;
        printf("The cards are: \n");

        while (temporaryCard != NULL) {
            printf("Card: %s\n", temporaryCard->name);
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
    } else {
        return value + '0';
    }
}