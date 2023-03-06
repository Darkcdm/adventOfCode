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
	
	void add(int value) {
		if (this->size >= this->cap) {
			this->increase();
		}
		this->values[this->size] = value;
	}

	void increase() {
		this->cap += 10;
		this->values = (int*)realloc(this->values, sizeof(int) * this->cap);
	}
};

struct Set {
	Set* sets;
	int cap;
	int size;

	Set() {
		this->cap = 10;
		this->size = 0;
		this->sets = (Set*)calloc(this->cap,sizeof(Set));
	}
};

struct Packet {
	Set set;
	Value value;

	void load(string line) {
		for (int i = 0; i < line.size(); i++) {
			if (line[i] == '[') {
				//create a new set
			}
		}
	}
};

struct Input {
	Packet* packets;
	int cap;
	int size;
	
	Input() {
		this->size = 0;
		this->cap = 10;
		this->packets = (Packet*)calloc(this->cap, sizeof(Packet));
	}

	void dealloc() {
		free(this->packets);
		this->cap = NULL;
		this->size = NULL;
	}

	void increase() {
		this->cap += 10;
		this->packets = (Packet*)realloc(this->packets, sizeof(Packet)*this->cap);
	}

	void load() {
		ifstream input;
		input.open("input.txt");
		
		string line;

		while (getline(input,line)) {
			if (this->size >= this->cap) {
				this->increase();
			}
			this->packets[this->size].load(line);
			this->size++;

			getline(input, line);

		}

		input.close();
	}
};

int main() {
	Input data;

	

	data.dealloc();
}