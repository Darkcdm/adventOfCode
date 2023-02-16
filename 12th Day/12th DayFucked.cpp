// 12th Day.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>

using namespace std;

class HeightMap {
public:
    int** coords;
    char** symbols;
    int height;
    int width;

    HeightMap() {
        this->height = 1;
        this->width = 1;

        this->coords = (int**)calloc(1, sizeof(int*));
        this->coords[0] = (int*)calloc(1, sizeof(int));

        this->symbols = (char**)calloc(1, sizeof(char*));
        this->symbols[0] = (char*)calloc(1, sizeof(char));
    }

    void printCoords() {
        for (int y = 0; y < this->height; y++) {
            for (int x = 0; x < this->width; x++) {
                cout << this->coords[y][x];
            }
            cout << endl;
        }
    }

    void printSymbols() {
        for (int y = 0; y < this->height; y++) {
            for (int x = 0; x < this->width; x++) {
                cout << this->symbols[y][x];
            }
            cout << endl;
        }
    }

    void squareAlloc(int size) {
        this->height = size;
        this->width = size;


            this->coords = (int**)realloc(this->coords, sizeof(int*)*size);
            this->symbols = (char**)realloc(this->symbols, sizeof(char*) * size);
            for (int i = 0; i < size; i++) {
                this->coords[i] = (int*)realloc(this->coords, sizeof(int) * size);
                this->symbols[i] = (char*)realloc(this->symbols, sizeof(char) * size);
            }
        
    }
};



void parseInput(HeightMap * map) {
    ifstream input("input.txt");

    string line;
    int lineCount = 0;

    map->width = 0;
    map->height = 0;

    while (getline(input, line)) {
        
        if (line.size() > map->width || line.size() > map->height) {
            map->squareAlloc(line.size());
        }

      
        for (int i = 0; i < line.size(); i++) {
            if (line[i] == 'S') {
                //map->coords[lineCount][i] = 0;
                map->symbols[lineCount][i] = line[i];
            }
            else if(line[i] == 'E') {
                //map->coords[lineCount][i] = 25;
                map->symbols[lineCount][i] = line[i];
            }
            else {
                int coordTest = (unsigned char)line[i] - 97;
                //map->coords[lineCount][i] = (unsigned char) line[i] - 97;
                map->symbols[lineCount][i] = line[i];
            }
            
        }

        lineCount++;
    }

    input.close();
}

int main()
{
    HeightMap map;

    parseInput(&map);

    //map.printCoords();

    cout << endl;

    map.printSymbols();

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
