#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <limits.h>

using namespace std;
struct Value {
	int* values;
	int cap;
	int size;

	Value() {
		this->cap = 10;
		this->size = 0;
		this->values = (int*)calloc(this->cap, sizeof(int));
	}

	void clear() {
		free(this->values);
		this->size = 0;
		this->cap = 0;
	}
};

struct Set {
	Set* sets;
	int cap;
	int size;

	Value values;

	Set() {
		this->cap = 10;
		this->size = 0;
		this->sets = (Set*)calloc(this->cap, sizeof(Set));
	}

	void parse(string line) {
		string selector;
		selector.clear;

		for (int i = 1; i < line.size(); i++) {
			
			if (line[i] == '[') {
				
			}
			if (line[i] == ']') {
				return;
			}
			if (line[i] == ',') {

			}
		}
	}

	void print() {

	}

	void clear() {
		this->values.clear();
		
		free(this->sets);
		this->cap;
		this->size = 0;
		this->cap = 0;
	}
};


int main() {

	Set left;
	Set right;

	ifstream input;

	bool doingLeft = true;

	input.open("input.txt");

	while (getline(input, line)) {
		if (line.size() == 0) {
			continue;
		}
		cout <<"Parsing: " << line << endl;

		cout << "Parsed: ";
		if (doingLeft) {
			left.parse();
			left.print();

			doingLeft = false;
		}
		else {
			right.parse();
			right.print();

			doingLeft = true;
		}
		cout << endl << endl;
	}


	input.close();

}