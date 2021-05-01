
void getUserInput(char * firstCommand, char * secondCommand, char * lastCommand) {
    char input[100];
    char * whiteSpaceSeparator;

    char tempInput[100];

    fgets(input, 100, stdin);
    int count = 0;

    strcpy(tempInput, input);
//HEllo

    whiteSpaceSeparator = strtok(tempInput, " ");
    while (whiteSpaceSeparator != NULL) {
        if (count == 0) {
            strcpy(firstCommand, whiteSpaceSeparator);
            count++;
            whiteSpaceSeparator = strtok(NULL, " ");
        } else if (count == 1) {
            strcpy(secondCommand, whiteSpaceSeparator);
            break;
        }
    }

    strcpy(lastCommand, input);
}
