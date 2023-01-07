#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Stack{
    char * content;
    unsigned size;
    unsigned capacity;
};

void printStatus(char * content){
    if (!strcmp(content, "DONE")){
        printf("%s\n", content);
    }
    else if (!strcmp(content, "FAIL")){
        printf("%s\n", content);
    }else{
        printf("%s.....", content);
    }
}

void loadStartInput (struct Stack ** stacks, FILE * input){

    printStatus("Loading Stacks");

    char cursor = (char) fgetc (input);

    int stackCount = 0;
    int spaceCount = 0;

    while (cursor != '*') {
        
        if (cursor == '['){
            spaceCount = 0;


            cursor = (char) fgetc (input);

            if (stacks[0][stackCount].capacity == 0 || stacks[0][stackCount].size >= stacks[0][stackCount].capacity){
                
                if (stacks[0][stackCount].capacity == 0){
                    stacks[0][stackCount].capacity = 1;
                }else{
                    stacks[0][stackCount].capacity = stacks[0][stackCount].capacity * 2;
                }

                stacks[0][stackCount].content = realloc(stacks[0][stackCount].content, stacks[0][stackCount].capacity);
            }

            stacks[0][stackCount].content[stacks[0][stackCount].size] = cursor;
            stacks[0][stackCount].size++;

            if (stackCount >= 9){
                printStatus("FAIL");
                exit(0);
            }else{
                stackCount++;
            }

        }
        if (cursor == '\n'){
            stackCount = 0;
        }
    
        if (cursor == ' '){
            spaceCount++;
        }

        if (spaceCount >= 4){
            stackCount++;
            spaceCount = 0;
        }


        cursor = (char) fgetc (input);
    } 

    printStatus("DONE");
}

void reverseStacks (struct Stack ** stacks){
    printStatus("reversing Stacks");
    
    for (int i = 0; i < 9; i++){
        char temp;
        unsigned len = stacks[0][i].size;

        for (unsigned j = 0; j < len/2; j++){
            temp = stacks[0][i].content[j];
            stacks[0][i].content[j] = stacks[0][i].content[len - j - 1];
            stacks[0][i].content[len - j - 1] = temp;
        }
    }
printStatus("DONE");
}

void printStacks (struct Stack * stacks){
    printStatus("printing Stacks");

    for (int i = 0; i < 9; i++){
        printf ("%d: %s \n", i+1, stacks[i].content);
    }
    
    printStatus("DONE");

}

void printTopStacks (struct Stack * stacks){
    printf("printing Top Stacks:\n");

    for (int i = 0; i < 9; i++){
        printf ("%d: %c\n", i+1, stacks[i].content[stacks[i].size-1]);
    }
}

void printTopStacksClean (struct Stack * stacks){
    printf("printing Top Stacks:\n");

    for (int i = 0; i < 9; i++){
        printf ("%c", stacks[i].content[stacks[i].size-1]);
    }
}

int loadOrders(FILE * input, int ** orders){
    char cursor = (char) fgetc(input);
    int orderCount = 0;

    char buffer[4];

    if (cursor == EOF){
        return 0;
    }

    while (cursor != '\n'){
        if (cursor == ' '){
            cursor = (char) fgetc(input);

            int count = 0;

            while (cursor >= '0' && cursor <= '9'){
                buffer[count] = cursor;
                count++;
                cursor = (char) fgetc(input);
            }
            buffer[count] = '\n';

            orders[0][orderCount] = (int) atoi(buffer);

            orderCount++;

            if (cursor == '\n'){
                break;
            }
        }
    cursor = (char) fgetc(input);
    }
    return 1;
}

void executeOrder(int * orders, struct Stack ** stacks){

    for (int i = 0; i < orders[0];i++){
        unsigned size1 = stacks[0][orders[2]-1].size;
        unsigned size2 = stacks[0][orders[1]-1].size;

        if (stacks[0][orders[2]-1].capacity <= size1){
            stacks[0][orders[2]-1].capacity = stacks[0][orders[2]-1].capacity * 2;
            stacks[0][orders[2]-1].content = realloc(stacks[0][orders[2]-1].content, stacks[0][orders[2]-1].capacity);
        }

        stacks[0][orders[2]-1].content[size1] = stacks[0][orders[1]-1].content[size2-1];
        stacks[0][orders[1]-1].content[size2-1] = 0;

        stacks[0][orders[2]-1].size++;
        stacks[0][orders[1]-1].size--;
    }

}

void executeNewOrder(int * orders, struct Stack ** stacks){

    if (orders[0] == 0){
        return;
    }

    char * buffer = calloc((unsigned)orders[0], sizeof(char));

    struct Stack * firstStack = &stacks[0][orders[1]-1];
    struct Stack * secondStack = &stacks[0][orders[2]-1];


    //load creates into the buffer and remove the from the first stack
    for (unsigned i = 0; i < (unsigned) orders[0]; i++){
        buffer[i] = firstStack->content[firstStack->size - 1 - i];
        firstStack->content[firstStack->size - 1 - i] = 0;
    }
    firstStack->size = firstStack->size - (unsigned) orders[0];

    unsigned oldCap = secondStack->capacity;
    //allocate memory into the second stack
    //make it larger
    while (secondStack->capacity <= oldCap + (unsigned) orders[0]){
        secondStack->capacity = secondStack->capacity * 2;
        secondStack->content = realloc(secondStack->content, secondStack->capacity);
    }
    //make it smaller
    while (secondStack->size + (unsigned) orders[0] < secondStack->capacity/2){
        secondStack->capacity = secondStack->capacity/2;
        secondStack->content = realloc(secondStack->content, secondStack->capacity);
    }

    //unload from buffer into the second stack
    for (int i = 0; i < orders[0]; i++){
        secondStack->content[secondStack->size] = buffer[orders[0] - 1 - i];
        secondStack->size++;
    }

    free(buffer);
}


int main (){
    struct Stack * stacks = calloc(9, sizeof(struct Stack));
    FILE * input = fopen("input", "r");
    int * orders = calloc(3, sizeof(int));

    loadStartInput(&stacks, input);

    reverseStacks(&stacks);


    printStatus("Moving Creates");
    while(loadOrders(input, &orders)){
        executeNewOrder(orders, &stacks);
    }
    printStatus("DONE");



    printTopStacksClean(stacks);
    
    fclose(input);
    free(orders);
    for(int i = 0; i < 9;i++){
        free(stacks[i].content);
    }
    free(stacks);
    return 0;
}