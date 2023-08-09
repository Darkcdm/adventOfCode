#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

string inputName;

struct Valve{
	string name;
	int flow;
	vector <int> routes;
};

void setInputs(bool setCheck) {
	if (setCheck) {
		inputName = "true_input.txt";

	}
	else {
		inputName = "test_input.txt";

	}
}

void sortInputFile() {
	fstream input;
	input.open(inputName);

	vector <string> lines;

	string line;
	while (getline(input, line)) {
		lines.push_back(line);
	}

	bool check;
	do {
		check = false;

		for (size_t i = 0; i < lines.size() - 1; i++) {
			string substr1 = lines[i].substr(6, 2);
			string substr2 = lines[i+1].substr(6, 2);
		
			if (substr1[1] > substr2[1]) {
				string buffer = lines[i];

				lines[i] = lines[i + 1];
				lines[i + 1] = buffer;

				check = true;

				break;
			}

		}
	} while (check);

	do {
		check = false;

		for (size_t i = 0; i < lines.size() - 1; i++) {
			string substr1 = lines[i].substr(6, 2);
			string substr2 = lines[i + 1].substr(6, 2);

			if (substr1[0] > substr2[0]) {
				string buffer = lines[i];

				lines[i] = lines[i + 1];
				lines[i + 1] = buffer;

				check = true;

				break;
			}

		}
	} while (check);

	for (size_t i = 0; i < lines.size(); i++) {
		cout << lines[i] << endl;
	}

	vector <string> nameList;

	for (size_t i = 0; i < lines.size(); i++) {
		nameList.push_back(lines[i].substr(6, 2));
	}

	for (size_t i = 0; i < lines.size(); i++) {
		
	}

}

int main(){
	setInputs(1);

	sortInputFile();


	return 0;
}