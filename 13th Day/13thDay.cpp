#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <limits.h>
#include <vector>
#include <sstream>

using namespace std;

std::vector<int> parseString(std::string* str) {
	std::vector<int> result;
	//Defines index that will go through the string -> i
	//&
	//Defines the max length of the string -> n
	int index = 0, strLength = str->size();
	//checks that we are not at the end of the file
	while (index < strLength) {
		//if the indexed value is open bracket, parse it more
		if ((*str)[index] == '[') {
			//j is the index without the first bracket
			int j = index + 1;

			//we find the other bracket ("]")
			while (j < strLength && (*str)[j] != ']') j++;
			if (j == strLength) {
				std::cerr << "Error: unmatched '['" << std::endl;
				return result;
			}
			std::string sub = str->substr(index + 1, j - index);
			std::vector<int> subResult = parseString(&sub);
			result.insert(result.end(), subResult.begin(), subResult.end());
			index = j + 1;
		}
		else if ((*str)[index] == ',') {
			index++;
		}
		else if (isdigit((*str)[index])) {
			int j = index + 1;
			while (j < strLength && isdigit((*str)[j])) j++;
			int value = std::stoi(str->substr(index, j - index));
			result.push_back(value);
			index = j;
		}
		else {
			std::cerr << "Error: invalid character '" << (*str)[index] << "'" << std::endl;
			return result;
		}
	}
	str->erase(0, index);
	return result;
}

vector<int> parseLine(string* str) {
	vector<int> result;

	int index = 0;

	while (index < str->length()) {
		if ((*str)[index] == '[') {

		}
	}

	str->erase(str->begin(), str->begin()+1);
	str->erase(str->end()-1, str->end());

	return result;
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

bool compareSets(string leftSet, string rightSet) {

}

int main() {
	string test = "[[1], [2, 3, 4]]";
	string output = test;
	int index = 0;

	for (int i = 0; i < test.size(); i++) {
		if (test[i] == '[') {
			int j = findPairBracket(test, i);
		
			output[i] = 97 + index;
			output[j] = 97 + index;
			index++;
		}


	}

	cout << test << endl;
	cout << output << endl;

	return 0;
}