// 11th Day.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <functional>
#include <cstdlib>
#include <fstream>
#include <string>
#include <cmath>
#include <list>

using namespace std;

class Test {
public:
    int testValue;
    int truy;
    int falsy;

    void setTestValue(int value) {
        this->testValue = value;
    }

    void setTruy(int value) {
        this->truy = value;
    }
    
    void setFalsy(int value) {
        this->falsy = value;
    }

};

class Operation {
public:
    char operand;
    int lvalue;
    int rvalue;

    void SetOperation(string order) {
        string word;
        
        int leftBracket = 1;
        int rightBracket = order.find(' ', leftBracket);

        word = order.substr(leftBracket, rightBracket);

        if (word.compare("old")) {
            this->lvalue = 0;
        }
        else {
            this->lvalue = (int)stoi(word);
        }

        this->operand = order[5];
        
        leftBracket = order.rfind(' ');
        rightBracket = order.size();
         
        word = order.substr(leftBracket, rightBracket);

        if (word == "old") {
            this->rvalue = 0;
        }
        else {
            this->rvalue = (int)stoi(word);
        }

    }
    
    int run(int old) {

        if (this->lvalue == 0) {
            int lvalue = old;
        }
        if (this->rvalue == 0) {
            int rvalue = old;
        }


        switch (operand) {
        case '+':
            return lvalue + rvalue;
            break;
        case '*':
            return lvalue * rvalue;
            break;
        default:
            cout << "Error at running operation";
            break;

        }
    }
};

class Items {
public:
    int size;
    int capacity;
    int* content;
    void addItem(int newItem) {

        if (this->size == this->capacity) {
            this->capacity = this->capacity + 10;
            this->content = (int*) realloc(this->content, sizeof(int)*this->capacity);
        }

        this->content[this->size] = newItem;
        this->size++;

    }
    int* removeItem() {
        int* returnValue = &this->content[0];

        for (int i = 1; i < this->size; i++) {
            this->content[i - 1] = this->content[i];
        }
        this->size--;

        if (this->size <= this->capacity - 10) {
            this->capacity= this->capacity - 10;
            this->content = (int*)realloc(this->content, sizeof(int) * this->capacity);
        }
        return returnValue;
    }
    
    void setStartingItems(string startingItems) {
        this->size = 0;
        this->capacity = 10;
        this->content = (int*)calloc(this->capacity, sizeof(Items));

        int cursor = 0;

        while (startingItems.find(',', cursor + 1) <= startingItems.size()) {
            this->addItem( (int) stoi(startingItems.substr(cursor + 1, startingItems.find(',', cursor))));

            cursor = (int)startingItems.find(',', cursor+1);
        }
        cursor++;
        this->addItem((int)stoi(startingItems.substr(cursor, startingItems.size())));
    }
};

class Monkey {
public:
    Items items;
    Operation operation;
    Test test;

    void print(int index) {
        cout << "Monkey " << index << ":\n";
        cout << "Starting items : ";
        
        for (int i = 0; i < this->items.size; i++) {
            cout << this->items.content[i] << ", ";
        }
        cout << endl;
  
        cout << "Operation : new = ";
        if (this->operation.lvalue == 0) {
            cout << "old";
        }
        else {
            cout << this->operation.lvalue;
        }

        cout << " " << this->operation.operand << " ";

        if (this->operation.rvalue == 0) {
            cout << "old";
        }
        else {
            cout << this->operation.rvalue;
        }

        cout << endl;

        cout << "Test : divisible by " << this->test.testValue;
        cout << endl;

        cout << "If true : throw to monkey " << this->test.truy;
        cout << endl;
        cout << "If false : throw to monkey " << this->test.falsy;
        cout << endl;
        cout << endl;
    }
};

void parseInput(Monkey **monkeys) {
    ifstream input("input.txt");
    string line;

    int monkeyIndex = 0;

    while (getline(input, line)) {

    
        Monkey* currentMonkey = &monkeys[0][monkeyIndex];
        for (int count = 0; count < 6; count++) {
            string startingItems;

            switch (count) {
                case 0:
                    //Monkey name
                    break;
                case 1:
                    //starting items
                    currentMonkey->items.setStartingItems(line.substr(17));
                    break;
                case 2:
                    //setting Operation
                    currentMonkey->operation.SetOperation(line.substr(18));
                    break;
                case 3:
                    //set testValue
                    currentMonkey->test.setTestValue((int)stoi(line.substr(line.rfind(' '), line.size())));
                    break;
                case 4:
                    //set outcome of test if true
                    currentMonkey->test.setTruy((int)stoi(line.substr(line.rfind(' '), line.size())));
                    break;
                case 5:
                    //set outcome of test if false
                    currentMonkey->test.setFalsy((int)stoi(line.substr(line.rfind(' '), line.size())));
                    break;
        
                default:
                    return;
            }
            getline(input, line);
        }
        currentMonkey->print(monkeyIndex);
        monkeyIndex++;
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
