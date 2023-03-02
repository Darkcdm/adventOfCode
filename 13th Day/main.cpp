#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <limits.h>

using namespace std;

struct Set {
	Set* sets;
	int setCap;
	int setSize;

	int* values;
	int valueCap;
	int valueSize;
	
	Set(){
		this->valueCap = 10;
		this->valueSize = 0;
		this->values = (int*)calloc(this->valueCap, sizeof(int));
	
		this->setCap = 10;
		this->setSize = 0;
		this->sets = (Set*)calloc(this->setCap, sizeof(Set));
	}

	Set* insertSet() {
		if (this->setSize >= this->setCap) {
			this->setCap += 10;
			this->sets = (Set*) realloc(this->sets, this->setCap);
		}
		
		Set* set = new Set;

		this->sets[this->setSize] = *set;
		this->setSize ++;

		return &this->sets[this->setSize--];
	}
	void insertValue(int value) {
		if (this->valueSize >= this->valueCap) {
			this->valueCap += 10;
			this->values = (int*)realloc(this->values, this->valueCap);
		}

		this->values[this->valueSize] = value;
		this->valueSize++;
	}
};

struct Packet {
	Set Left;
	Set Right;

	void parse(string line) {

	}
};

string scanForSet() {
	string stringSet;

	return stringSet;
}

int main() {

	int size = 0;
	int cap = 0;
	Packet* packets;

	ifstream input;
	input.open("input.txt");
	
	string line;
	while (getline(input, line)) {
		cap++;
	}
	
	input.close();
	input.open("input.txt");

	packets = (Packet*)calloc(cap, sizeof(Packet));

	while (getline(input, line)) {
		Set* pastSet = NULL;
		Set* currentSet = &packets->Left;

		for (int charIndex = 0; charIndex < line.size(); charIndex++) {
			if (line[charIndex] == '[') {
				currentSet = currentSet->insertSet();
			}

		}
		
		size++;
	}
	cout << size;
}