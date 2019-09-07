/**********************************************
* Name: Cesar Zavala *
* Date: 09/08/2019 *
* Assignment: Project 1 - Sequence and Order validation *
***********************************************
* This program validates if a specific file format and sequence of characters in the file are valid. *
***********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**********************************************
* Description: *Prints the full operation with the mismatch highlighted in bold.
* Input: *Takes in the operation string, its length, the last open bracket location, and the mismatch location.
* Output: *No output but prints into the console.
***********************************************/
void printBoldError(char string[], int length, int lastOpen, int errorLoc) {
    for (int i = 0; i < length; i++) {
        //printf("0");
        if (i == lastOpen) printf("\e[1m%c\e[0m", string[i]);
        else if (i == errorLoc) printf("\e[1m%c\e[0m", string[i]);
        else printf("%c", string[i]);
    }
    printf("\n");
}

/**********************************************
* Description: *Validates the operation given by checking for bracket order.
* Input: *The operation to be validated (a string), and its length.
* Output: *A number that is used later y the switch for the onsole output.
***********************************************/
int validateOperation(char op[], int length) {
    int position, lastOpenBracket = 0; //makeshift stack counters.
    char charStack[36];
    int bracketLoc[36];
//    char errorShow[36];
        //printf("String is %s with length %d \n", op, length); //debug
        position = 0;
        for (int i = 0; i < length; i++) {
            char currentChar = op[i];
            switch (currentChar) {
                case ' ':
                    break;
                case '{':
                    //lastOpenBracket = i;
                    charStack[position] = '{';
                    bracketLoc[position] = i;
                    position++;
                    break;
                case '[':
                    //lastOpenBracket = i;
                    charStack[position] = '[';
                    bracketLoc[position] = i;
                    position++;
                    break;
                case '(':
                    //lastOpenBracket = i;
                    charStack[position] = '(';
                    bracketLoc[position] = i;
                    position++;
                    break;
                case '}':
                    if (position == 0) {
                        //printf("Position is negative (debug)\n");
                        return 3;
                    }
                    if (charStack[position - 1] != '{') {
                        //printf("bracket mismatch '}'\n"); //debug
                        printBoldError(op, length, bracketLoc[position-1], i);
                        return 1;
                    } else {
                        position--;
                    }
                    break;
                case ']':
                    if (position == 0) {
                        //printf("Position is negative (debug)\n");
                        return 3;
                    }
                    if (charStack[position - 1] != '[') {
                        //printf("bracket mismatch ']'\n");
                        printBoldError(op, length, bracketLoc[position-1], i);
                        return 1;
                    } else {
                        position--;
                    }
                    break;
                case ')':
                    if (position == 0) {
                        //printf("Position is negative (debug)\n");
                        return 3;
                    }
                    if (charStack[position - 1] != '(') {
                        //printf("bracket mismatch ')'\n");
                        printBoldError(op, length, bracketLoc[position-1], i);
                        return 1;
                    } else {
                        position--;
                    }
                    break;
                default:
                    //printf("invalid char %c\n", &currentChar);
                    return 2;
            }
        }
        if(position != 0) return 3;
        //printf("%d",position);
return 0;
}

/**********************************************
* Description: *Main method that takes care of file IO and the structure validation of the file to be read.
* Input: *It takes a file name as its only parameter.
* Output: *Returns an integer, but its real output is the validation of every operation in the console.
***********************************************/
int main(int argc, char *argv[]) {

    if (argc < 2) { //
        printf("Please input the file path!\n");
        return 0;
    }
    FILE *fp;
//    printf(argv[1]); //debug
//    printf("\n");
    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("File invalid or doesn't exist\n");
        exit(0);
    }
//    printf("File exists!\n"); //debug
    char operation[36];
    int caseN;
    fscanf(fp, "%d", &caseN);
    if (caseN > 10 || caseN < 0) {
        printf("Expression number not in range (0-10)");
        fclose(fp);
        exit(0);
    }
    for (int i = 1; i <= caseN; i++) //no error checking
    {
        int status;
        if(fscanf(fp, "%s", operation) != EOF) {
            status = validateOperation(operation, strlen(operation)); //validation of sequences.
        }
        else status = 99;
        switch(status){
            case 0:
                printf("Operation %d is valid.\n",i);
                break;
            case 1:
                printf("Operation %d is not valid (bracket mismatch).\n",i);
                break;
            case 2:
                printf("Operation %d is not valid (invalid character or invalid size).\n",i);
                break;
            case 3:
                printf("Operation %d is not valid (missing brackets or too many brackets).\n",i);
                break;
            default:
                printf("Empty line.\n");
            break;
        }
    }

    fclose(fp);
    return 0;
}



