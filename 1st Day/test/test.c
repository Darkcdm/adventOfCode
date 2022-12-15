#include <stdio.h>
#include <stdlib.h>

struct test{
    int value;
};

void fuckItUp(struct test ** tester){
    tester[0] = (struct test *) realloc(tester[0], sizeof(struct test)*100);

    for(int i = 0; i < 10; i++){
        tester[0][i].value = 10-i;
    }

}

void printTheFucker(struct test * tester){
    for (int i = 0; i < 10; i++ ){
        printf("index: %d value:%d\n", i, tester[i].value);
    }
}

int main(){
    struct test * tester = calloc(1, sizeof(struct test));

    fuckItUp(&tester);

    printTheFucker(tester);

    free(tester);
    return 0;
}