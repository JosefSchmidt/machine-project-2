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



void createDefaultCardList() {
    struct card * newCard;
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
                char name [] = {cardValue, cardType, '\0'};

                if(headerHasBeenSet == 0) {
                    strcpy(head->name, name);
                    head->previous = NULL;
                    head->next = NULL;
                    headerHasBeenSet = 1;
                    last = head;
                }
                else {
                    newCard = (struct card *)malloc(sizeof (struct card));
                    strcpy(newCard->name, name);
                    newCard->previous = head;
                    newCard->next = NULL;

                    last->next = newCard;
                    last = newCard;
                }
            }
        }

        printf("Cards has been successfully created!\n\n");
    }
}

void displayCardListFromFirst() {
    struct card * temporaryCard;

    if(head == NULL) {
        printf("The deck is empty");
    } else {
        temporaryCard = head;
        printf("The cards are: \n");

        while(temporaryCard != NULL) {
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