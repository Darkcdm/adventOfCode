// 11th Day.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <functional>
#include <cstdlib>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

class Test {
public:
    int testValue;
    int truy;
    int falsy;
};

class Monkey {
public:
    int *items;
    Test test;
};

void parseInput(Monkey **monkeys) {
    ifstream input("input.txt");
    string line;

    for (int count = 0; count < 7; count++) {
        getline(input, line);

        switch (count) {
        case 0:
            //Monkey name
            break;
        case 1:
            line.substr()
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        
        default:
            return;
        }
        
    }

    input.close();
}

int main()
{
    Monkey* monkeys = (Monkey*)calloc(10, sizeof(Monkey));



    parseInput(&monkeys);


    free(monkeys);
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
