#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <limits.h>
#include <vector>
#include <sstream>

using namespace std;

struct Set {

	string original;
	string bracketMap;
	int value;
	int rightIndex;
	int leftIndex;

	Set(string str) {
		this->original = str;
		this->bracketMap = this->markBrackets(str);
		this->value = NULL;
		this->rightIndex = 0;
		this->leftIndex = 0;
	}

	int getValue() {
		this->leftIndex = this->rightIndex;

		this->rightIndex = this->original.find(',', leftIndex);

		this->value = stoi(this->original.substr(leftIndex, rightIndex));

		return this->value;
	}
	int getSet() {

	}

	int findPairBracket(string str, int bracketPosition) {
		bracketPosition++;
		while (bracketPosition < str.size()) {
			if (str[bracketPosition] == ']') {
				break;
			}
			if (str[bracketPosition] == '[') {
				bracketPosition = findPairBracket(str, bracketPosition);
			}

			bracketPosition++;
		}

		return bracketPosition;
	}

	string markBrackets(string str) {
		string output = str;
		int index = 0;

		for (int i = 0; i < str.size(); i++) {
			if (str[i] == '[') {
				int j = this->findPairBracket(str, i);

				output[i] = 97 + index;
				output[j] = 97 + index;
				index++;
			}
		}

		return output;
	}



};

int compareSets(Set left, Set right) {
	cout << "-Compare" << left.original <<" vs" << right.original << endl;


	if (left.getValue() < right.getValue()) {
		return 1;
	}
	else {
		return 0;
	}

	
	return 0;
}

int main() {

	Set left("[1,1,3,1,1]");
	Set right("[1,1,5,1,1]");

	cout << left.original << endl;
	cout << left.bracketMap << endl << endl;

	cout << right.original << endl;
	cout << right.bracketMap << endl;

	cout <<endl<< "== Pair 1 ==" <<endl;
	
	int check = compareSets(left, right);
	if (check == -1) {
		cout << "YOU FUCKED UP COMPARING";
		return 1;
	}
	if (check) {
		cout << "Left side is smaller, so inputs are in the right order" << endl;
		return 0;
	}
	else {
		cout << "Right side is smaller, so inputs are not in the right order" << endl;
		return 0;
	}
	

	return 0;
}