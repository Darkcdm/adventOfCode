// 10th Day.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

class Command {
    public:
        string type = "";
        int amount = 0;

        void parse(string line) {
            this->type = line.substr(0, 4);
            if (line.length() > 4) {

            
            this->amount = stoi(line.substr(4));
            }
            else {
                amount = 0;
            }
        }
};

class System {
public:
    int cycle = 0;
    int regX = 1;

    void cycleUp() {
        cycle++;
        printPixel();
        
    }

    void printPixel() {
        if (cycle >= regX - 1 && cycle <= regX + 1) {
            cout << "#";
        }
        else {
            cout << ".";
        }
        

        if (cycle % 40 == 0) {
            cout << endl;
            cycle = 0;
        }
    }

    void addRegX(int addValue) {
        regX = regX + addValue;
    }
};

void selectivePrint(int regX, int cycle) {
    int strength = cycle * regX;

    if (cycle == 20) {
        cout << strength << endl;
    }
    if (cycle == 60) {
        cout << strength << endl;
    }
    if (cycle == 100) {
        cout << strength << endl;
    }
    if (cycle == 140) {
        cout << strength << endl;
    }
    if (cycle == 180) {
        cout << strength << endl;
    }
    if (cycle == 220) {
        cout << strength << endl;
    }
}

int main()
{
    ifstream input("input.txt");
    string line;

    int cycle = 0;
    int regX = 1;

    bool isCommandRunning = false;

    int addValue;
    Command command;
    System system;
   
    int lineCount = 0;

    while (lineCount != 144) {


        system.cycleUp();

        if (isCommandRunning) {
            isCommandRunning = false;

            system.addRegX(addValue);
        }
        else {
            lineCount++;
            
            
            getline(input,line);
            
            

            command.parse(line);
            if (command.type == "addx") {
                addValue = command.amount;
                isCommandRunning = true;
            }
        }
        
    }
    
    input.close();
}

//1 + 15 - 11 + 6 - 3 + 5 - 1 - 8 + 13 + 4 = 21
//1   16   5    11  8   13  12  4   17   21

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
