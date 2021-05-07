#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma once


// Function declarations
char getDeckType();

char getDeckValue();

int getHighestCardPosition();

void deleteCardList();

void printHiddenBoard();

int cardExistsInDeck();

void splitShuffleDeck();

int getLengthOfCard();

void printBoard();

void showAllCards();

int getColumnInteger();

int getCardValue();

struct card {
    char name[3];
    int x;
    int y;
    int visible;
    int fPosition;
    struct card *next;
    struct card *previous;
} *head, *last;

void createDefaultCardList(char *message) {
    struct card *newCard;
    int headerHasBeenSet = 0;

    head = (struct card *) malloc(sizeof(struct card));

    if (head == NULL) {
        strcpy(message, "Error! Unable to allocate memory");
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
                    head->visible = 0;
                    head->x = x;
                    head->y = y;
                    headerHasBeenSet = 1;
                    last = head;
                } else {
                    newCard = (struct card *) malloc(sizeof(struct card));
                    strcpy(newCard->name, name);
                    newCard->previous = last;
                    newCard->next = NULL;
                    newCard->visible = 0;
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
    }
}

void SaveDeckOfCards(char filePath[], char *message) {
    //"\Users\steve\CLionProjects\machine-project-2\Card.txt"
    FILE *in_file = fopen(filePath, "w");

    struct card *current = head;

    while (current != NULL) {//loops trough the deck until it is empty.

        fprintf(in_file, "%s %s", current->name, "\n"); //print the cards in the file.
        current = current->next;//set next card to current.
    }
    fclose(in_file);
    strcpy(message, "Deck saved in file");
}

void uploadDeckOfCards(char filePath[], char *message) {

    // "/Users/josefschmidt/Desktop/machine-project-2/Card.txt"
    FILE *in_file = fopen(filePath, "r");

    // test for files not existing.
    if (in_file == NULL) {
        deleteCardList();
        strcpy(message, "Error! File could not be found");
        return;
    }

    // Delete the current card list
    deleteCardList();

    struct card *newCard;
    int headerHasBeenSet = 0;
    head = (struct card *) malloc(sizeof(struct card));

    if (head == NULL) {
        strcpy(message, "Error! Unable to allocate memory");
        return;
    }
    int y = 0;
    int x = 0;
    int cardCount = 0;

    char line[3];

    // Load in the cards from file and validate cards
    while (fscanf(in_file, "%s", line) != EOF) {

        if (cardCount == 52) {
            deleteCardList();
            strcpy(message, "Error! File has to many deck of cards. Limit is 52");
            return;
        }

        if (headerHasBeenSet == 0) {
            strcpy(head->name, line);
            head->previous = NULL;
            head->next = NULL;
            head->visible = 0;
            head->x = x;
            head->y = y;
            headerHasBeenSet = 1;
            last = head;
        } else {
            int alreadyExists = cardExistsInDeck(line);

            if (alreadyExists == 1) {
                strcpy(message, "Error! Deck is not valid. Has duplicate values");
                return;
            }
            newCard = (struct card *) malloc(sizeof(struct card));
            strcpy(newCard->name, line);
            newCard->previous = last;
            newCard->next = NULL;
            newCard->visible = 0;
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


int cardExistsInDeck(const char cardName[]) {
    struct card *current = head;

    while (current != NULL) {
        if (strcmp(current->name, cardName) == 0) {
            return 1;
        }

        if (current->next != NULL) {
            current = current->next;
        } else {
            return 0;
        }
    }

}

void splitShuffleDeck(int cardPosition, char *message) {
    struct card *current = head;

    struct card *firstPileLast = NULL;
    struct card *secondPileFirst = NULL;

    // Create 2 linkedList and add
    int count = 0;

    // Split the deck
    while (current->next != NULL) {
        count = count + 1;
        if (count == cardPosition) {
            firstPileLast = current;
            secondPileFirst = current->next;
        } else {
            current = current->next;
        }
    }


    struct card *newHead = (struct card *) malloc(sizeof(struct card));;
    struct card *newLast = (struct card *) malloc(sizeof(struct card));;

    if (newHead == NULL) {
        strcpy(message, "Error! Unable to allocate memory");
        printHiddenBoard();
        return;
    }


    int headerHasBeenSet = 0;

    int y = 0;
    int x = 0;

    while (firstPileLast != NULL || secondPileFirst != NULL) {

        if (headerHasBeenSet == 0) {
            strcpy(newHead->name, firstPileLast->name);
            newHead->visible = firstPileLast->visible;
            newHead->previous = NULL;
            newHead->next = NULL;
            newHead->x = x;
            newHead->y = y;
            headerHasBeenSet = 1;
            newLast = newHead;

            firstPileLast = firstPileLast->previous;

            if (x < 6) {
                x = x + 1;
            } else {
                x = 0;
                y = y + 1;
            }
        } else {

            if (firstPileLast != NULL) {
                // First deck
                struct card *newCard = (struct card *) malloc(sizeof(struct card));
                strcpy(newCard->name, firstPileLast->name);
                newCard->previous = newLast;
                newCard->visible = firstPileLast->visible;
                newCard->next = NULL;
                newCard->x = x;
                newCard->y = y;

                newLast->next = newCard;
                newLast = newCard;

                firstPileLast = firstPileLast->previous;

                if (x < 6) {
                    x = x + 1;
                } else {
                    x = 0;
                    y = y + 1;
                }
            }

            if (secondPileFirst != NULL) {
                // First deck
                struct card *newCard = (struct card *) malloc(sizeof(struct card));
                strcpy(newCard->name, secondPileFirst->name);
                newCard->visible = secondPileFirst->visible;
                newCard->previous = newLast;
                newCard->next = NULL;
                newCard->x = x;
                newCard->y = y;

                newLast->next = newCard;
                newLast = newCard;

                secondPileFirst = secondPileFirst->next;

                if (x < 6) {
                    x = x + 1;
                } else {
                    x = 0;
                    y = y + 1;
                }
            }
        }
    }

    deleteCardList();

    head = newHead;
    last = newLast;
    printBoard(message);

}

void shuffleDeck(char *message) {
    struct card *current = head;

    struct card *newHead = (struct card *) malloc(sizeof(struct card));
    struct card *newLast = (struct card *) malloc(sizeof(struct card));

    int headerHasBeenSet = 0;


    // Split the deck
    while (current != NULL) {

        // Place it at random spot in new pile
        if (headerHasBeenSet == 0) {
            strcpy(newHead->name, current->name);
            newHead->previous = NULL;
            newHead->next = NULL;
            newHead->visible = current->visible;
            headerHasBeenSet = 1;
            newLast = newHead;
        } else {
            int length = getLengthOfCard(newHead);
            int random = 0;
            if (length != 0) {
                random = rand() % length;
            }
            int count = 0;
            struct card *newCurrent = newHead;

            while (1) {
                if (count == random) {
                    struct card *newCard = (struct card *) malloc(sizeof(struct card));
                    strcpy(newCard->name, current->name);
                    newCard->previous = newCurrent;
                    newCard->next = newCurrent->next;
                    newCard->visible = current->visible;
                    newCurrent->next = newCard;
                    newCurrent->next->previous = newCard;
                    break;
                } else {
                    count = count + 1;
                    newCurrent = newCurrent->next;
                }
            }
        }
        current = current->next;
    }

    // Set x and y to all the cards in the new head
    int y = 0;
    int x = 0;

    current = newHead;
    while (current->next != NULL) {
        current->x = x;
        current->y = y;
        current = current->next;
        if (x < 6) {
            x = x + 1;
        } else {
            x = 0;
            y = y + 1;
        }
    }

    // Update the linkedList
    head = newHead;
    last = newLast;
    printBoard(message);
}

int getLengthOfCard(struct card header) {
    struct card *current = &header;
    int counter = 0;

    while (current != NULL) {
        counter = counter + 1;
        current = current->next;
    }

    return counter;
}

void sortGameCards() {
    struct card *current = head;
    int countx = 1;
    int county = 0;
    while (current != NULL) {
        if (current->previous == NULL) {
            current->x = 0;
            current->y = 0;
        } else {
            current->x = countx;
            current->y = county;


            // Determine the visibility of a card
            if (county == 0 && countx > 0) {
                current->visible = 0;
            } else if (county == 1 && countx > 1) {
                current->visible = 0;
            } else if (county == 2 && countx > 2) {
                current->visible = 0;
            } else if (county == 3 && countx > 3) {
                current->visible = 0;
            } else if (county == 4 && countx > 4) {
                current->visible = 0;
            } else if (county == 5 && countx > 5) {
                current->visible = 0;
            } else {
                current->visible = 1;
            }

            // Determine the x and y position of a card
            if (county == 5 && countx == 6) {
                countx = 2;
                county = county + 1;
            } else if (county == 6 && countx == 6) {
                countx = 3;
                county = county + 1;
            } else if (county == 7 && countx == 6) {
                countx = 4;
                county = county + 1;
            } else if (county == 8 && countx == 6) {
                countx = 5;
                county = county + 1;
            } else if (county == 9 && countx == 6) {
                countx = 6;
                county = county + 1;
            } else if (countx == 6) {
                county = county + 1;
                countx = 1;
            } else {
                countx = countx + 1;
            }
        }
        current = current->next;
    }
}

void showAllCards() {
    struct card *current = head;

    while (current != NULL) {
        current->visible = 1;
        current = current->next;
    };
}


void extendedCardMove(char *columnName, char *moverName, char *destinationName, char *message) {
    struct card *mover = NULL;
    struct card *destination = NULL;
    struct card *fCard = NULL;
    struct card *current = head;


    int columnNr = getColumnInteger(columnName);

    // Not valid column name
    if (columnNr == -1) {
        strcpy(message, "Error: No a valid input form");
        return;
    }

    // It's a column
    while (current != NULL) {
        if (strcmp(moverName, current->name) == 0) {
            if (current->visible != 1) {
                strcpy(message, "Error: MoverCard is not visible");
                return;
            } else if ((current->x != columnNr) && current->fPosition != columnNr) {
                strcpy(message, "Error: MoverCard not in specfied column");
                return;
            }
            mover = current;
            current = head;
            break;
        }
        current = current->next;
    }

    int destinationNr = getColumnInteger(destinationName);

    if (destinationNr == 10 || destinationNr == 20 || destinationNr == 30 || destinationNr == 40) {

        int found = 0;
        while (current != NULL) {
            if (current->fPosition == destinationNr) {
                fCard = current;
                found = 1;
                current = head;
                break;
            }
            current = current->next;
        }

        if (found == 1) {
            // Check if card value is one timer larger than moverCard
            if (fCard->name[1] == mover->name[1]) {
                char input1[2] = {fCard->name[0]};
                char input2[2] = {mover->name[0]};
                int fCardValue = getCardValue(input1);
                int moverCardValue = getCardValue(input2);
                if (moverCardValue - fCardValue == 1) {
                    mover->fPosition = fCard->fPosition;
                    mover->x = -1;
                    mover->y = -1;
                    fCard->fPosition = -1;
                } else {
                    strcpy(message, "Error: Move not allowed");
                    return;
                }
            } else {
                strcpy(message, "Error: Move not allowed");
                return;
            }
        } else {
            current = head;

            // Is the moverCard for the correct f destination and is it an es
            if (mover->name[0] == 'A') {
                if (
                        (mover->name[1] == 'C' && destinationNr == 10) ||
                        (mover->name[1] == 'D' && destinationNr == 20) ||
                        (mover->name[1] == 'H' && destinationNr == 30) ||
                        (mover->name[1] == 'S' && destinationNr == 40)
                        ) {
                    mover->x = -1;
                    mover->y = -1;
                    mover->fPosition = destinationNr;
                } else {
                    strcpy(message, "Error: Move not allowed");
                    return;
                }
            } else {
                strcpy(message, "Error: Move not allowed");
                return;
            }
        }

    }


    int highestCount = -1;

    while (current != NULL) {
        if (destinationNr == current->x && highestCount < current->y) {
            highestCount = current->y;
            destination = current;
        }
        current = current->next;
    }
    current = head;


    if (destination == NULL) {
        int previousY = mover->y;
        int previousX = mover->x;

        mover->y = 0;
        mover->x = destinationNr;


        if (previousY > 0) {
            while (current != NULL) {
                if (current->x == previousX && current->y == previousY - 1) {
                    current->visible = 1;
                    break;
                }
                current = current->next;
            }
            current = head;
        }


        // Do the same for mover's children
        int count = 1;

        while (current != NULL) {
            if (current->x == previousX && current->y == previousY + count) {
                current->y = mover->y + count;
                current->x = destinationNr;
                count = count + 1;
                current = head;
            }
            current = current->next;
        }
        current = head;

    } else {
        if (mover->name[1] != destination->name[1]) {
            char input1[2] = {mover->name[0]};
            char input2[2] = {destination->name[0]};

            int moverValue = getCardValue(input1);
            int destinationValue = getCardValue(input2);
            if (destinationValue - moverValue == 1) {
                int previousY = mover->y;
                int previousX = mover->x;

                mover->y = destination->y + 1;
                mover->x = destination->x;

                if (previousY > 0) {
                    while (current != NULL) {
                        if (current->x == previousX && current->y == previousY - 1) {
                            current->visible = 1;
                            break;
                        }
                        current = current->next;
                    }
                    current = head;
                }

                // Do the same for mover's children
                int count = 1;
                while (current != NULL) {
                    if (current->x == previousX && current->y == previousY + count) {
                        current->y = mover->y + count;
                        current->x = destination->x;
                        count = count + 1;
                        current = head;
                    }
                    current = current->next;
                }
                current = head;
            }

        } else {
            strcpy(message, "Error: Move not allowed");
            return;
        }
    }


    strcpy(message, "OK");


}

void cardMove() {

}

int getColumnInteger(char *columnName) {

    // Columns
    if (strcmp(columnName, "C1") == 0) {
        return 0;
    } else if (strcmp(columnName, "C2") == 0) {
        return 1;
    } else if (strcmp(columnName, "C3") == 0) {
        return 2;
    } else if (strcmp(columnName, "C4") == 0) {
        return 3;
    } else if (strcmp(columnName, "C5") == 0) {
        return 4;
    } else if (strcmp(columnName, "C6") == 0) {
        return 5;
    } else if (strcmp(columnName, "C7") == 0) {
        return 6;
    }
        // Sections
    else if (strcmp(columnName, "F1") == 0) {
        return 10;
    } else if (strcmp(columnName, "F2") == 0) {
        return 20;
    } else if (strcmp(columnName, "F3") == 0) {
        return 30;
    } else if (strcmp(columnName, "F4") == 0) {
        return 40;
    } else {
        return -1;
    }
};

int getCardValue(char *cardNumber) {
    if (strcmp(cardNumber, "A") == 0) {
        return 1;
    } else if (strcmp(cardNumber, "2") == 0) {
        return 2;
    } else if (strcmp(cardNumber, "3") == 0) {
        return 3;
    } else if (strcmp(cardNumber, "4") == 0) {
        return 4;
    } else if (strcmp(cardNumber, "5") == 0) {
        return 5;
    } else if (strcmp(cardNumber, "6") == 0) {
        return 6;
    } else if (strcmp(cardNumber, "7") == 0) {
        return 7;
    } else if (strcmp(cardNumber, "8") == 0) {
        return 8;
    } else if (strcmp(cardNumber, "9") == 0) {
        return 9;
    } else if (strcmp(cardNumber, "T") == 0) {
        return 10;
    } else if (strcmp(cardNumber, "J") == 0) {
        return 11;
    } else if (strcmp(cardNumber, "Q") == 0) {
        return 12;
    } else if (strcmp(cardNumber, "K") == 0) {
        return 13;
    } else {
        return -1;
    }
}