#include <stdio.h>
#include <stdlib.h>
struct Set{
int min, max;
};

struct Buffer{
char * content;
int length;
int size;
};

char * parseString(char condition, FILE * file){
    struct Buffer buffer;

    buffer.content = calloc(8, sizeof(char));
    buffer.length = 0;
    buffer.size = 8;

    char cursor = (char) fgetc(file);
    while (cursor != condition){
        if (cursor == EOF){
            return "-1";
        }
        buffer.content[buffer.length++] = cursor;
        cursor = (char) fgetc(file);
    }

    char * returnValue = buffer.content;

    return returnValue;
}

void  loadSets(struct Set* set1, struct Set* set2, FILE* file){

    char * min;
    char * max;

    min = parseString('-', file);
    max = parseString(',', file);


    set1->min = (int) atoi(min);
    set1->max = (int) atoi(max);

    min = parseString('-', file);
    max = parseString('\n', file);

    set2->min = (int) atoi(min);
    set2->max = (int) atoi(max);

    free(min);
    free(max);
}

int main(){
    FILE * file = fopen("input","r");
    struct Set set1;
    struct Set set2;

    int immersedSets = 0;

    loadSets(&set1, &set2, file);

    while (set1.min != -1){
        if (set1.min >= set2.min && set1.min <= set2.max){
            immersedSets++;
        }
        else if(set1.max >= set2.min && set1.max <= set2.max){
            immersedSets++;
        }
        else if (set2.min >= set1.min && set2.min <= set1.max){
            immersedSets++;
        }
        else if(set2.max >= set1.min && set2.max <= set1.max){
            immersedSets++;
        }


        loadSets(&set1, &set2, file);
    }
    fclose(file);
    
    printf("%d\n",immersedSets);

    return 0;
}