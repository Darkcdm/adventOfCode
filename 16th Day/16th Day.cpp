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

vector <Valve> parseInputFile() {
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
	vector <int> flowList;
	vector <string> routesList;

	for (size_t i = 0; i < lines.size(); i++) {
		nameList.push_back(lines[i].substr(6, 2));
		string flowString = lines[i].substr(lines[i].find('=') + 1,lines[i].find(';') - 1 - lines[i].find('='));

		flowList.push_back(stoi(flowString));

		routesList.push_back(lines[i].substr(lines[i].find("valves") + 7, lines[i].size() - lines[i].find("valves")));

		cout << routesList[i] << endl;
	}


	vector<Valve> valves;

	for (size_t i = 0; i < nameList.size(); i++) {

		Valve valve;

		valve.name = nameList[i];
		valve.flow = flowList[i];


		string routeString = routesList[i];




		valves.push_back(valve);

	}
	return valves;

}

int main(){

	vector <Valve> valves;
	setInputs(1);

	valves = parseInputFile();


	return 0;
}