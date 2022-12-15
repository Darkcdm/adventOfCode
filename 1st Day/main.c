#include <stdio.h>
#include <stdlib.h>

struct elf {

    unsigned int index;
    unsigned long long calories;
};

unsigned int loadElfs(struct elf ** elfArr){
    char * filename = "input.txt";
    FILE * input = fopen(filename, "r");
    unsigned int elfCount = 0;
    unsigned arrCap = 1;

    char cursor = (char) fgetc(input);
    
    unsigned int bufferLim = 8;
    char * buffer = calloc(8, sizeof(char));
    

    //reading the whole file
    while (cursor != EOF){
    unsigned bufferCount = 0;


        //reading the whole line
        while(1){
         
            //checking that the Buffer is big enough for the the line
            if(bufferCount == bufferLim){
                buffer = realloc(buffer, sizeof(struct elf) * bufferLim * 2);
                bufferLim = bufferLim * 2;   
            }

            //saving the cursor into the buffer
            buffer[bufferCount] = cursor;
            bufferCount++;


            if(cursor == '\n' || cursor == EOF){
                break;
            }

            //incrementing the index of reading characters
            cursor = (char) fgetc(input);
        }

        if (buffer[0] == '\n'){
            elfCount++;
            if (elfCount >= arrCap){
                arrCap = (elfCount + 1) * 10;
                elfArr[0] = (struct elf *) realloc(elfArr[0], arrCap * sizeof(struct elf));

                for (unsigned i = arrCap-1; i >= elfCount; i--){
                    elfArr[0][i].calories = 0;
                }
            }
        }else{
            int calories = atoi(buffer);
            elfArr[0][elfCount].index = elfCount;
            elfArr[0][elfCount].calories = calories + elfArr[0][elfCount].calories;
        }

    cursor = (char) fgetc(input);
    }    


    fclose(input);
    free(buffer);

    return elfCount + 1;
}

void printElfs(struct elf * elfArr, unsigned int elfCount){
    for (unsigned i = 0; i < elfCount; i++){
        printf("elf %u: has %llu calories\n", elfArr[i].index, elfArr[i].calories);
    }
}

void searchForMostCalories(struct elf * elfArr, unsigned int elfCount){
    unsigned max1CaloriesIndex = 0;
    unsigned max2CaloriesIndex = 0;
    unsigned max3CaloriesIndex = 0;
    

    for (unsigned i = 0; i < elfCount; i++){
        if (
        max1CaloriesIndex != i && 
        elfArr[i].calories >= elfArr[max1CaloriesIndex].calories){
            max1CaloriesIndex = i;
        }
    }

    for (unsigned i = 0; i < elfCount; i++){
        if (
        max2CaloriesIndex != i && 
        elfArr[i].calories >= elfArr[max2CaloriesIndex].calories && 
        elfArr[i].calories != elfArr[max1CaloriesIndex].calories){
            max2CaloriesIndex = i;
        }
        
    }

    for (unsigned i = 0; i < elfCount; i++){
        if (max3CaloriesIndex != i && 
        elfArr[i].calories >= elfArr[max3CaloriesIndex].calories &&
        elfArr[i].calories != elfArr[max1CaloriesIndex].calories &&
        elfArr[i].calories != elfArr[max2CaloriesIndex].calories
        ){
            max3CaloriesIndex = i;;
        }
        
    }    

    printf("\n\n The highest calories value found is %llu\n", elfArr[max1CaloriesIndex].calories);
    
    unsigned long long int sumMaxCalories = elfArr[max3CaloriesIndex].calories + elfArr[max2CaloriesIndex].calories + elfArr[max1CaloriesIndex].calories;

    printf("\n\n The SUM of the best three calories is: %llu", sumMaxCalories);
}

int main(){

    struct elf * elfArr = calloc(1, sizeof(struct elf));
    
    unsigned int elfCount;

    elfCount = loadElfs(&elfArr);

    printf("There are %u elfs in arr\n", elfCount);
    printf("The first elf has %llu calories\n", elfArr[0].calories); 
    printf("The last elf has %llu calories\n", elfArr[elfCount - 1].calories);   
    
    printElfs(elfArr, elfCount);

    searchForMostCalories(elfArr, elfCount);

    free(elfArr);
    return 0;
}