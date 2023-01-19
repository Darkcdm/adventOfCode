#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Tree {
    unsigned X;
    unsigned Y;
    unsigned height;
    int counted;
};

struct Forest {
    unsigned width;
    unsigned height;
    struct Tree ** trees;
};


void addTree(struct Forest * forest, unsigned X, unsigned Y, unsigned height){

    if(Y >= forest->height){

        forest->height = Y;

        forest->trees = realloc(forest->trees, forest->height * sizeof(struct Tree));
    }

    if(X >= forest->width){

        forest->width = X;

        for (unsigned i = 0; i < forest->height; i++){
            forest->trees[i] = realloc(forest->trees[i], forest->width * sizeof(struct Tree));
        }
    }

    struct Tree * tree = &forest->trees[Y][X];

    tree->counted = 0;
    tree->X = X;
    tree->Y = Y;
    tree->height = height;
}

void loadForest(struct Forest * forest){
    FILE * input = fopen("input.txt", "r");
    char cursor = (char) fgetc(input);

    unsigned Y = 0;
    while (cursor != EOF){


        unsigned X = 0;
        while(cursor != '\n' && cursor != EOF){

            unsigned height = (unsigned) atoi(&cursor);

            addTree(forest, X, Y, height);

            cursor = (char) fgetc(input);
            X++;
        }
        cursor = (char) fgetc(input);
        Y++;
    }

    fclose(input);
}

unsigned getScenery(struct Forest forest, int X, int Y){
    unsigned scoreTop = 0, scoreBottom = 0, scoreLeft = 0, scoreRight = 0;

    unsigned houseHight = forest.trees[Y][X].height;

    if (X == 0 || X == (int) forest.width-1 || Y == 0 || Y == (int) forest.height-1){
        return 0;
    }

    for (int y = Y-1; y >= 0; y--){
        scoreTop++;

        struct Tree tree = forest.trees[y][X];

        if (tree.height >= houseHight){
            break;
        }
    }

    for (int x = X-1; x >= 0; x--){
        scoreLeft++;

        struct Tree tree = forest.trees[Y][x];

        if (tree.height >= houseHight){
            break;
        }
    }

    for(int y = Y+1; y < (int) forest.height; y++){
        scoreBottom++;

        struct Tree tree = forest.trees[y][X];

        if (tree.height >= houseHight){
            break;
        }
    }

   for(int x = X+1; x < (int) forest.width; x++){
        scoreRight++;

        struct Tree tree = forest.trees[Y][x];

        if (tree.height >= houseHight){
            break;
        }
    }

    return scoreTop*scoreLeft*scoreBottom*scoreRight;
}

unsigned findMaxScenery(struct Forest forest){

    unsigned maxScore = 0;

    for (int y = 0; y < (int) forest.height; y++){
        for(int x = 0; x < (int) forest.width; x++){
        
            unsigned score = getScenery(forest, x, y);

            if (score > maxScore) maxScore = score;
        }
    }

    return maxScore;
}

int main (){
    struct Forest forest;
    forest.width = 99;
    forest.height = 99;
    forest.trees = calloc(forest.height, sizeof(struct Tree));
    for(unsigned i = 0; i < forest.height; i++){
        forest.trees[i] = calloc(forest.width, sizeof(struct Tree));
    }


    loadForest(&forest);

    printf("%u", findMaxScenery(forest));

    return 0;
}