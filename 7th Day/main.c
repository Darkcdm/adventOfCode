#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Directory{
    struct Directory * parent;
    char * name;
    struct Directory * children;
    unsigned long weight;    
    unsigned long size;
    unsigned long capacity;
};

void destructDirectory(struct Directory * dir){

    if (dir->size == 0){
        //free(dir->name);
        if (dir->capacity != 0){
            free(dir->children);
        }
        dir->parent = NULL;
    }else{
        destructDirectory(&dir->children[dir->size-1]);
        dir->size--;
    }
}

void createDirectory(struct Directory * dir, char * name, struct Directory * parent){
    printf("creating directory named: %s\n", name);

    dir->parent = parent;
    dir->children = NULL;
    dir->weight = 0;
    dir->name = calloc(strlen(name), sizeof(char));
    strcpy(dir->name, name);
    dir->size = 0;
    dir->capacity = 0;
}

void loadWord(char * cursor, char ** buffer, FILE * input){
    int count = 0;
    while(*cursor != '\n' && *cursor != ' '){
        if (*cursor == EOF){
            buffer = NULL;
            return;
        }
        buffer[0][count++] = *cursor;
        *cursor = (char) fgetc(input);
    }
    buffer[0][count] = '\0';
}

void updateWeights(struct Directory * dir){
    if(dir->size != 0){
        for (unsigned long i = 0; i < dir->size; i++){
            updateWeights(&dir->children[i]);
        }
    }

    if (dir->parent != NULL){
        dir->parent->weight = dir->parent->weight + dir->weight;
    }
}

void printFolders(struct Directory * dir){
    if(dir->size != 0){
        for(unsigned long i = 0; i < dir->size; i++){
            printFolders(&dir->children[i]);
        }
    }
    printf("%s = %lu\n", dir->name, dir->weight);
}

unsigned long printSum(struct Directory * dir){
    unsigned long SUM = 0;

    if (dir->weight <= 100000){
        SUM = SUM + dir->weight;
    }

    for(unsigned long i = 0; i < dir->size; i++){
        SUM = SUM + printSum(&dir->children[i]);
    }

    return SUM;
}

unsigned long printSmol(struct Directory * dir, unsigned long temp){
    unsigned long SMOL = temp;

    if (dir->weight == 8465165){
        printf("catch\n");
    }

    if (dir->weight >= 8381165 && dir->weight <= SMOL){
        SMOL = dir->weight;
    }
    for(unsigned long i = 0; i < dir->size; i++){
        SMOL = printSmol(&dir->children[i], SMOL);

    }


    return SMOL;
}

int main (){
    printf("Starting the program\n");

    struct Directory root;
    createDirectory (&root, "/", NULL);

    struct Directory * activeDirectory = NULL;

    FILE * input = fopen ("input.txt", "r");
    char cursor = (char) fgetc(input);    

    char * buffer = calloc(16, sizeof(char));
    char * arg = calloc(16, sizeof(char));


    //while we are not at the end of the file
    while (cursor != EOF){

        loadWord(&cursor, &buffer, input);

        if (!strcmp (buffer, "cd")){
            cursor = (char) fgetc (input);
            loadWord(&cursor, &arg, input);

            if(!strcmp (arg,"/")){
                activeDirectory = &root;
            }
            else if (!strcmp(arg,"..")){
                activeDirectory = activeDirectory->parent;
            }else{
                for(unsigned long i=0;i<activeDirectory->size;i++){
                    if(!strcmp(arg,activeDirectory->children[i].name)){
                        activeDirectory = &activeDirectory->children[i];
                    }
                }
            }

        }

        if (!strcmp (buffer, "ls")){
            cursor = (char) fgetc(input);

            while(cursor != '$' && cursor != EOF){
                loadWord(&cursor, &arg, input);

                if(!strcmp(arg, "dir")){
                    cursor = (char) fgetc(input);

                    loadWord(&cursor, &arg, input);

                    struct Directory temp;
                    createDirectory(&temp, arg, activeDirectory);

                        activeDirectory->capacity++;
                    if(activeDirectory->capacity == 0){
                        activeDirectory->children = calloc(activeDirectory->capacity, sizeof(struct Directory));
                    }else{
                        activeDirectory->children = realloc(activeDirectory->children, sizeof(struct Directory)*activeDirectory->capacity);
                    }
                    activeDirectory->children[activeDirectory->size++] = temp;

                }else{
                    activeDirectory->weight = activeDirectory->weight + (unsigned long) atoi(arg);

                    printf("%s weight = %lu\n", activeDirectory->name, activeDirectory->weight);

                }
                cursor = (char) fgetc(input);
            }
        }

        cursor = (char) fgetc(input);
    }

    

    free(buffer);
    free(arg);

    updateWeights(&root);

    printf("\n-------------------------\n");

    printFolders(&root);

    printf("\n%lu\n",printSum(&root));   

    printf("\n%lu\n",printSmol(&root, 70000000));

    printf("\n%lu\n",printSmol(&root, printSmol(&root, 70000000)));


    destructDirectory(&root);

    printf("Program Done\n");
    return 0;
}