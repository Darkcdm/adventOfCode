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
    long long testValue;
    long long truy;
    long long falsy;

    void setTestValue(long long value) {
        this->testValue = value;
    }

    void setTruy(long long value) {
        this->truy = value;
    }
    
    void setFalsy(long long value) {
        this->falsy = value;
    }

    long long run(long long item) {
        if (item % this->testValue == 0) {
            return this->truy;
        }
        else {
            return this->falsy;
        }
        return -1;
    }
};

class Operation {
public:
    long long iteration;
    char operand;
    long long lvalue;
    long long rvalue;

    void SetOperation(string order) {
        string word;
        
        this->iteration = 0;

        long long leftBracket = 1;
        long long rightBracket = order.find(' ', leftBracket);

        word = order.substr(leftBracket, rightBracket);


        this->lvalue = 0;


        this->operand = order[5];
        
        leftBracket = order.rfind(' ');
        rightBracket = order.size();
         
        word = order.substr(leftBracket, rightBracket);

        if (word.compare(" old") == 0) {
            this->rvalue = 0;
        }
        else {
            this->rvalue = (long long)stoi(word);
        }

    }
    
    long long run(long long old) {
        this->iteration++;

        long long lvalue = this->lvalue;
        long long rvalue = this->rvalue;


        if (this->lvalue == 0) {
            lvalue = old;
        }

        if (this->rvalue == 0) {
            rvalue = old;
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
            return -1;
            break;

        }
        return -1;
    }
};

class Items {
public:
    long long size;
    long long capacity;
    long long* content;
    void addItem(long long newItem) {

        if (this->size == this->capacity) {
            this->capacity = this->capacity + 10;
            this->content = (long long*) realloc(this->content, sizeof(long long)*this->capacity);
        }

        this->content[this->size] = newItem;
        this->size++;

    }
    long long removeItem() {

        if (this->size <= 0) {
            return NULL;
        }

        long long returnValue = this->content[0];

        for (long long i = 1; i < this->size; i++) {
            this->content[i - 1] = this->content[i];
        }
        this->size--;

        if (this->size <= this->capacity - 10) {
            this->capacity= this->capacity - 10;
            this->content = (long long*)realloc(this->content, sizeof(long long) * this->capacity);
        }
        return returnValue;
    }
    
    void setStartingItems(string startingItems) {
        this->size = 0;
        this->capacity = 10;
        this->content = (long long*)calloc(this->capacity, sizeof(Items));

        long long cursor = 0;

        while (startingItems.find(',', cursor + 1) <= startingItems.size()) {
            this->addItem( (long long) stoi(startingItems.substr(cursor + 1, startingItems.find(',', cursor))));

            cursor = (long long)startingItems.find(',', cursor+1);
        }
        cursor++;
        this->addItem((long long)stoi(startingItems.substr(cursor, startingItems.size())));
    }
};

class Monkey {
public:
    Items items;
    Operation operation;
    Test test;

    void printItems(long long index) {
        cout << "Monkey " << index <<":";

        for (long long i = 0; i < this->items.size; i++) {
            cout << this->items.content[i] << ", ";
        }
        cout << endl;
    }

    void print(long long index) {
        cout << "Monkey " << index << ":\n";
        cout << "Starting items : ";
        
        for (long long i = 0; i < this->items.size; i++) {
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

long long parseInput(Monkey** monkeys) {
    ifstream input("input.txt");
    string line;

    long long monkeyIndex = 0;

    while (getline(input, line)) {


        Monkey* currentMonkey = &monkeys[0][monkeyIndex];
        for (long long count = 0; count < 6; count++) {
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
                currentMonkey->test.setTestValue((long long)stoi(line.substr(line.rfind(' '), line.size())));
                break;
            case 4:
                //set outcome of test if true
                currentMonkey->test.setTruy((long long)stoi(line.substr(line.rfind(' '), line.size())));
                break;
            case 5:
                //set outcome of test if false
                currentMonkey->test.setFalsy((long long)stoi(line.substr(line.rfind(' '), line.size())));
                break;

            default:
                return -1;
            }
            getline(input, line);
        }
        currentMonkey->print(monkeyIndex);
        monkeyIndex++;
    }
    input.close();

    return monkeyIndex;
}

int main()
{
    long long ROUNDS = 10000;

    Monkey* monkeys = (Monkey*)calloc(10, sizeof(Monkey));
    long long troopSize = parseInput(&monkeys);

    cout << endl;



    for (long long r = 1; r <= ROUNDS; r++) {

        for (long long i = 0; i < troopSize; i++) {
            Monkey* selectedMonkey = &monkeys[i];

            while (selectedMonkey->items.size != 0) {
                long long selectedItem = selectedMonkey->items.removeItem();
                if (selectedItem != NULL) {

                    selectedItem = selectedMonkey->operation.run(selectedItem);
                    //selectedItem = selectedItem / 3;
                    long long targetMonkey = selectedMonkey->test.run(selectedItem);
                    monkeys[targetMonkey].items.addItem(selectedItem);
                }
            }




        }

        /*
        cout << "round: " << r << endl;
        for (long long i = 0; i < troopSize; i++) {
            monkeys[i].printItems(i);
        }
        cout << endl;
        */
        if (r % 1000 == 0 || r == 1 || r == 20) {
            for (long long i = 0; i < troopSize; i++) {
                cout << "Monkey " << i << " :" << monkeys[i].operation.iteration << endl;
            }
            cout << endl;
        }
    }

    cout << endl;
    for (long long i = 0; i < troopSize; i++) {
        cout << "Monkey " << i << " :" << monkeys[i].operation.iteration << endl;
    }

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
