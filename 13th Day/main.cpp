#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <limits.h>

using namespace std;

struct Value {
	int* values;
	int valueCap;
	int valueSize;
};

struct Set {
	Set* sets;
	int setCap;
	int setSize;
};

struct Packet {
	Set set;
	Value value;
};


int main() {

}