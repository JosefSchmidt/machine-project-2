
void getUserInput(char *firstCommand, char *secondCommand, char *lastCommand) {
    char input[100];
    char tempInput[100];
    char *whiteSpaceSeparator;
    int count = 0;

    fgets(input, 100, stdin);

    // Remove new line after in string after using fgets
    input[strcspn(input, "\n")] = 0;

    strcpy(tempInput, input);

    whiteSpaceSeparator = strtok(tempInput, " ");
    while (whiteSpaceSeparator != NULL) {
        if (count == 0) {
            strcpy(firstCommand, whiteSpaceSeparator);
            count++;
            whiteSpaceSeparator = strtok(NULL, " ");
            strcpy(secondCommand, "");
        } else if (count == 1) {
            strcpy(secondCommand, whiteSpaceSeparator);
            break;
        }
    }

    strcpy(lastCommand, input);
}
