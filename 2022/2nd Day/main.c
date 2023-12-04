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
        return 0; 
    break;
    }

    if (
        right == 'X' && left == 'A' ||
        right == 'Y' && left == 'B' ||
        right == 'Z' && left == 'C'        
    ){
        return returnScore + 3;
    }




    if (right == 'X' && left == 'C'){
        return returnScore + 6;
    }

    if (right == 'Y' && left == 'A'){
        return returnScore + 6;
    }

    if (right == 'Z' && left == 'B'){
        return returnScore + 6;
    }

    return returnScore + 0;
}
char getWin(char left){
    if(left == 'A'){
        return 'B';
    }

    if(left == 'B'){
        return 'C';
    }


    return 'A';


}

char getDraw(char left){
    return left;
}

char getLoose(char left){
    if(left == 'A'){
        return 'C';
    }

    if(left == 'B'){
        return 'A';
    }


    return 'B';


}


int getScoreExtra(char left ,char right){

    if (right == 'Z'){
        right = getWin(left);
    }
    if (right == 'Y'){
        right = getDraw(left);
    }
    if (right == 'X'){
        right = getLoose(left);
    }


    int returnScore = 0;

    switch (right){
    case 'A':
        returnScore = 1;
    break;
    case 'B':
        returnScore = 2;
    break;
    case 'C':
        returnScore = 3;
    break;
    default:
        printf("Invalid right value");
        return 0; 
    break;
    }

    if (left == right){
        return returnScore + 3;
    }




    if (right == 'A' && left == 'C'){
        return returnScore + 6;
    }

    if (right == 'B' && left == 'A'){
        return returnScore + 6;
    }

    if (right == 'C' && left == 'B'){
        return returnScore + 6;
    }

    return returnScore + 0;
}

int main(){
    char * filename = "input";

    FILE * file = fopen(filename, "r");

    char * line = malloc(sizeof(char)*5);

    int totalScore = 0;

    while (fgets(line, 5, file)){
        

        char left = line[0];
        char right = line[2];
        int levelScore = getScoreExtra(left, right);

        totalScore += levelScore;

    }
    fclose(file);
    free(line);

    printf("Total Score: %d\n", totalScore);

    return 0;
}