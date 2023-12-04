#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void load(char ** scope, char input){
    scope[0][13] = input;
}

void shift(char ** scope){

    for (int i = 1; i < 14; i++){
        scope[0][i-1] = scope[0][i];
    }
}

int compare(char * scope){

    for(int i=0; i < 4; i++){
        if (scope[i] == 0){
            return 0;
        }
    }
    

   int check = 1;
    for (int a = 0; a < 14; a++){
        for (int b = 0; b < 14; b++){
            if (scope[a] == scope[b] && a != b){
                check = 0;
            }
        }
    }
    return check;
}

int main(){
    
    FILE * input = fopen("input.txt", "r");
    char cursor = (char) fgetc(input);
    char * scope = calloc(14, sizeof(char));
    int freqOffset = 1;

    if (cursor == 0){
        return 1;
    }

    while (cursor != '\n' || cursor != EOF){
        load(&scope, cursor);
        if (compare(scope)){
            break;
        }
        shift(&scope);

        cursor = (char) fgetc(input);

        freqOffset++;
    }

    free(scope);
    fclose(input);

    printf("%d\n", freqOffset);
     
    return 0;
}