//yeah this is fucked
/*

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

	Value values;

	Set() {
		this->cap = 10;
		this->size = 0;
		this->sets = (Set*)calloc(this->cap,sizeof(Set));
	}
};

/*
struct Packet {
	Set set;

	void load(string line) {
		string selector;

		for (int i = 0; i < line.size(); i++) {
			switch (line[i]) {
			case '[':
				//create new set


				break;
			case ']':
				//end current set

				break;
			case ',':
				//save selector as a value

				break;
			default:
				//save into the current selector

				break;
			}
		}
	}

	void print() {
		this->set
	}
};



struct Input {
	Set* packets;
	int cap;
	int size;
	
	Input() {
		this->size = 0;
		this->cap = 10;
		this->packets = (Set*)calloc(this->cap, sizeof(Set));
	}

	void dealloc() {
		free(this->packets);
		this->cap = NULL;
		this->size = NULL;
	}

	void increase() {
		this->cap += 10;
		this->packets = (Set*)realloc(this->packets, sizeof(Set)*this->cap);

	}

	void load() {
		ifstream input;
		input.open("input.txt");
		
		string line;

		while (getline(input,line)) {
			if (line.size() == 1) {
				continue;
			}

			if (this->size >= this->cap) {
				this->increase();
			}
			this->packets[this->size].load(line);
			this->size++;

			getline(input, line);

		}

		input.close();
	}

	void print() {
		
		for (int i = 0; i < this->size; i++) {
			this->packets[i].print();
		}
	}
};

int main() {
	Input data;

	data.load();

	data.print();

	data.dealloc();
}

*/