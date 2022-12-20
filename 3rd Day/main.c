#include <stdio.h>
#include <stdlib.h>


static char * filename = "input";

struct Backpack{
    char * content;
    char * leftPart;
    char * rightPart;
    unsigned length;
    unsigned size;
};

struct Duplicates
{
    char * content;
    unsigned length;
    unsigned size;
};

void loadBackPack(struct Backpack * backpack, FILE * input){
    backpack->length = 0;
    free(backpack->content);
    backpack->content = calloc(backpack->size, sizeof(char));

    char cursor = (char) fgetc(input);
    
    if (cursor == EOF || cursor == 0){
        backpack->content = NULL;
    }

    while (cursor!= '\n' && cursor != EOF){
        //dynamically allocate more memory
        if (backpack->length >= backpack->size){
            backpack->size = backpack->size * 2;
            backpack->content = realloc(backpack->content, backpack->size);
        }
        //assign cursor to backpack content
        backpack->content[backpack->length] = cursor;
        backpack->length++;
        cursor = (char) fgetc(input);
    }
    


        if (backpack->leftPart != NULL){
            free(backpack->leftPart);
        }

        backpack->leftPart = calloc((backpack->length/2)+1, sizeof(char));

        for (unsigned i = 0; i < backpack->length/2; i++){
            backpack->leftPart[i] = backpack->content[i];
        }

        backpack->leftPart[backpack->length/2] = '\n';

        if (backpack->rightPart != NULL){
            free(backpack->rightPart);
        }

        backpack->rightPart = calloc((backpack->length/2)+1, sizeof(char));

        
        for (unsigned i = backpack->length/2; i < backpack->length; i++){
            unsigned index = i - backpack->length/2;
            backpack->rightPart[index] = backpack->content[i];
        }

        backpack->rightPart[backpack->length/2] = '\n';
    
}

char findDuplicates(struct Backpack backpack){
    for (unsigned leftIndex = 0; leftIndex < backpack.length/2; leftIndex++){
        for (unsigned rightIndex = 0; rightIndex < backpack.length/2; rightIndex++){
            if (backpack.leftPart[leftIndex] == backpack.rightPart[rightIndex]){
                return backpack.leftPart[leftIndex];
            }
        }
    }
    return 0;
}

unsigned long long getScore(char duplicate){
    unsigned long long value;
    value = 10;
    value = (unsigned long long) (duplicate);
    
    if(value > 96){
        return value - 96;
    }else{
        return value - 65 + 27;
    }
    return 0;
}

int main(){
    struct Backpack backpack;
    backpack.content = calloc(8, sizeof(char));
    backpack.leftPart = NULL;
    backpack.rightPart = NULL;
    backpack.length = 0;
    backpack.size = 8;
    
    struct Duplicates duplicates;
    duplicates.content = calloc(8, sizeof(char));
    duplicates.length = 0;
    duplicates.size = 8;

    FILE * input = fopen(filename, "r");

    loadBackPack(&backpack, input);

    while (backpack.content != NULL){

        if (duplicates.length >= duplicates.size){
            duplicates.size = duplicates.size * 2;
            duplicates.content = realloc(duplicates.content, sizeof(char)*duplicates.size);
        }
    
        duplicates.content[duplicates.length] = findDuplicates(backpack);
        duplicates.length++;

        loadBackPack(&backpack, input);
    }

    fclose(input);

    free(backpack.content);
    free(backpack.leftPart);
    free(backpack.rightPart);

    unsigned long long score = 0;

    for (int i = 0; i < duplicates.length; i++){
        score = score + getScore(duplicates.content[i]);
    }
    printf("%llu", score);

    free(duplicates.content);
    return 0;
}