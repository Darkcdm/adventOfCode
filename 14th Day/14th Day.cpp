// 14th Day.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <string>


using namespace std;

struct Cell {
    int x;
    int y;
    int trueX;
    int trueY;
    
    bool occupied;
    bool solid;
    char symbol;

    Cell(int x, int y) {
        this->x = x;
        this->y = y;

        occupied = false;
        solid = false;
        symbol = '.';
    }
};

//returns Top Left and Bottom Right Coords
vector<int> parseDimension() {
    vector<int> results;

    ifstream input;
    input.open("input.txt");

    string line;

    while (getline(input, line)) {
        int leftIndex = 0;
        int rightIndex = 0;

        while(rightIndex != line.size()) {
            leftIndex = rightIndex;
            rightIndex = line.find(' ', leftIndex+1);
            
            if (rightIndex == -1) {
                rightIndex = line.size();
            }

            string coords = line.substr(leftIndex, rightIndex - leftIndex);

            if (coords[1] == '-') {
                leftIndex = rightIndex;
                rightIndex = line.find(' ', leftIndex + 1);

                if (rightIndex == -1) {
                    rightIndex = line.size();
                }

                coords = line.substr(leftIndex, rightIndex - leftIndex);
            }

            string strX = coords.substr(0, coords.find(','));
            string strY = coords.substr(coords.find(',')+1);

            int x = stoi(strX);
            int y = stoi(strY);
      
            if (results.empty()) {
                results.push_back(x);
                results.push_back(y);
                results.push_back(x);
                results.push_back(y);
            }

            if (x < results[0]) {
                results[0] = x;
            }
            if (y < results[1]) {
                results[1] = y;
            }
            if (x > results[2]) {
                results[2] = x;
            }
            if (y > results[3]) {
                results[3] = y;
            }


        }
    }

    input.close();

    return results;
}

void printCave(vector<vector<Cell>> cave) {

}

vector<vector<Cell>> createCave(int depth, int width, int leftX) {
    vector<vector<Cell>> result;

    for (int y = 0; y < depth; y++) {
        for (int x = 0; x < width; x++) {

        }
    }

    return result;
}

int main(){
    vector<int> dimensions = parseDimension();

    vector<vector<Cell>> cave = createCave(dimensions[3], dimensions[2] - dimensions[0] + 2, dimensions[2]);

    cout << dimensions[0] << ", ";
    cout << dimensions[1] << ", ";

    cout << dimensions[2] << ", ";
    cout << dimensions[3] << ", ";


    printCave(cave);
}
