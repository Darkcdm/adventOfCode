#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Folder{
    struct Folder * parent;
    char * name;
    struct Folder * children;    
    struct File * files;
};

struct File{
    struct Folder * parent;
    unsigned size;
    char * name;
};

struct Files{
    struct File * content;
    unsigned size;
    unsigned capacity;
};


void insertIntoTheList(unsigned size,char * name, struct Files ** files){
    for(unsigned i=0;i<files[0]->size;i++){
        if (strcmp(files[0]->content[i].name,name) == 0){
            return;
        }
    }

    if (files[0]->size >= files[0]->capacity){
        files[0]->capacity = files[0]->capacity + 10;
        files[0]->content = realloc(files[0]->content, sizeof(struct File)*files[0]->capacity);
    }
    files[0]->content[files[0]->size].name = calloc(strlen(name), sizeof(char));
    strcpy(files[0]->content[files[0]->size].name, name);
    files[0]->content[files[0]->size].size = size;
    files[0]->content[files[0]->size].parent = NULL;

    files[0]->size++;
}

void loadFiles(struct Files ** files){
    FILE * input = fopen("input.txt", "r");

    char cursor = (char) fgetc(input);

    unsigned bufferSize;
    char * bufferName = calloc(16, sizeof(char));
    char * buffer = calloc(16, sizeof(char));

    //reading the whole file
    while (cursor != EOF){

        //reading the line
        if (cursor >= '0' && cursor <= '9'){
            
            unsigned count = 0;

            while (cursor != ' '){
                buffer[count] = cursor;
                count++;
                cursor = (char) fgetc(input);
            }

            buffer[count] = '\n';
            bufferSize = (unsigned) atoi(buffer);

            count = 0;
            cursor = (char) fgetc(input);
            while (cursor != '\n'){
                buffer[count] = cursor;
                count++;
                cursor = (char) fgetc(input);
            }
            buffer[count] = '\n';

            strcpy(bufferName, buffer);


            insertIntoTheList(bufferSize, bufferName, &files[0]);



        }else{
            while (cursor!= '\n'){
                cursor = (char) fgetc(input);
            }
        }
        cursor = (char) fgetc(input);

    }

    free(buffer);
    fclose(input);
}

int main (){
    struct Files * files = calloc(1, sizeof(struct Files));
    files->content = calloc(10, sizeof(struct File));
    files->capacity = 10;
    files->size = 0;
    
    //unsigned sumResult = 0;


    loadFiles(&files);

    printf("%u", files->size);

    return 0;
}