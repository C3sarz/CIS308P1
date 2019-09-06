#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void validateOperation(char op[], int length)
{
    int position,totalN,curlyN,squareN,curveN,lastBracket = 0; //makeshift stack counters.
    if(length > 1){
        printf("String is %s with length %d \n",op,length);//debug
//        while(position < length){
//
//        }
    }

//return 0;
}

int main(int argc, char *argv[]) {

    if(argc < 2){ //
        printf("Please input the file path!\n");
        return 0;
    }
    FILE *fp;
//    printf(argv[1]); //debug
//    printf("\n");
    fp = fopen(argv[1],"r");
    if(fp == NULL){
        printf("File invalid or doesn't exist\n");
        exit(0);
    }
//    printf("File exists!\n"); //debug
    char operation[36];
    int caseN;
    fscanf(fp,"%d",&caseN);
    if(caseN > 10 || caseN < 0)
    {
        printf("Expression number not in range (0-10)");
        fclose(fp);
        exit(0);
    }
    for(int i = 1;i <= caseN;i++) //no error checking
    {
        fscanf(fp,"%s",operation);
        validateOperation(operation,strlen(operation));
        //
        //
    }

    fclose(fp);
    return 0;
}



