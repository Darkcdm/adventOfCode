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

char findTriplicate(struct Backpack backpack1,struct Backpack backpack2, struct Backpack backpack3){
    for (int i = 0; i < backpack1.length; i++){
        for (int j = 0; j < backpack2.length; j++){
            for (int k = 0; k < backpack3.length; k++){
                if (backpack1.content[i] == backpack2.content[j] && backpack1.content[i] == backpack3.content[k]){
                    return backpack1.content[i];
                }
            }
        }
    }
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

void initBackpack(struct Backpack * backpack){
    backpack->content = calloc(8, sizeof(char));
    backpack->leftPart = NULL;
    backpack->rightPart = NULL;
    backpack->length = 0;
    backpack->size = 8;
}

void initDuplicate(struct Duplicates * duplicate){
        duplicate->content = calloc(8, sizeof(char));
        duplicate->length = 0;
        duplicate->size = 8;
}

void loadGroup(struct Backpack * Backpack1, struct Backpack * Backpack2, struct Backpack * Backpack3, FILE * input){
    loadBackPack(Backpack1, input);
    loadBackPack(Backpack2, input);
    loadBackPack(Backpack3, input);
}

void destroyBackpack(struct Backpack * backpack){
    free(backpack->leftPart);
    free(backpack->rightPart);
    free(backpack->content);
}

int main(){
    struct Backpack firstBackpack;
    struct Backpack secondBackpack;
    struct Backpack thirdBackpack;

    initBackpack(&firstBackpack);
    initBackpack(&secondBackpack);
    initBackpack(&thirdBackpack);

    struct Duplicates duplicates;
    initDuplicate(&duplicates);

    FILE * input = fopen(filename, "r");

    loadGroup(&firstBackpack,&secondBackpack,&thirdBackpack, input);

    while(firstBackpack.content != NULL){

        if (duplicates.length >= duplicates.size){
            duplicates.size = duplicates.size * 2;
            duplicates.content = realloc(duplicates.content, sizeof(char)*duplicates.size);
        }
    
        duplicates.content[duplicates.length] = findTriplicate(firstBackpack, secondBackpack, thirdBackpack);
        duplicates.length++;

        loadGroup(&firstBackpack,&secondBackpack,&thirdBackpack, input);
    }

    fclose(input);

    destroyBackpack(&firstBackpack);
    destroyBackpack(&secondBackpack);
    destroyBackpack(&thirdBackpack);


    unsigned long long score = 0;

    for (unsigned i = 0; i < duplicates.length; i++){
        score = score + getScore(duplicates.content[i]);
    }
    printf("%llu", score);

    free(duplicates.content);
    return 0;
}