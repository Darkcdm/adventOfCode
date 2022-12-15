#include <stdio.h>
#include <stdlib.h>

int getScore(char left, char right){
    int returnScore = 0;

    switch (right){
    case 'X':
        returnScore = 1;
    break;
    case 'Y':
        returnScore = 2;
    break;
    case 'Z':
        returnScore = 3;
    break;
    default:
        printf("Invalid right value");
        return NULL; 
    break;
    }

    if (left == right){
        return returnScore + 2;
    }
    
}

int main(){
    char * filename = "input";

    FILE * file = fopen(filename, "r");

    char * line = malloc(sizeof(char)*4);

    int totalScore = 0;
    fgets(line, 4, file);
    while (line != NULL){
        

        char left = line[0];
        char right = line[2];
        int levelScore = getScore(left, right);

        totalScore += levelScore;
        fgets(line, 4, file);
    }
    fclose(file);
    free(line);

    printf("Total Score: %d\n", totalScore);

    return 0;
}