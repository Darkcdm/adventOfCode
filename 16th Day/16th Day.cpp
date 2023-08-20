#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

string inputName;

struct Valve{
	int id;
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


int findMatchingIndex(const std::vector<std::string>& strings, const std::string& target) {
	for (int i = 0; i < strings.size(); ++i) {
		if (strings[i] == target) {
			return i;  // Return the index of the first match
		}
	}

	return -1;  // Return -1 if no match is found
}

vector <Valve> sortInputFile() {
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

	vector <string> nameList;
	vector <int> flowList;
	vector <vector<string>> routeList;

	for (size_t i = 0; i < lines.size(); i++) {
		nameList.push_back(lines[i].substr(6, 2));
		flowList.push_back(stoi(lines[i].substr(lines[i].find("= ") + 2, lines[i].find("= ") + 2 - lines[i].find(';'))));
	
		vector<string> lineRouteList;

		string routeString = lines[i].substr(lines[i].find("to valves") + 9, lines[i].find("to valves") + 9 -  lines[i].size());
		
		string selected;
		int routeStringIndex = 0;

		char cursor;
		for (cursor = routeString[routeStringIndex]; routeStringIndex < routeString.size(); cursor = routeString[++routeStringIndex]) {
			if (cursor != '\n' && cursor != ' ' && cursor != ',') {
				selected.push_back(cursor);
			}
			
			if (cursor == '\n' || cursor == ',') {
				lineRouteList.push_back(selected);
				selected.clear();
			}

		} 
		//selected.push_back(cursor);
		lineRouteList.push_back(selected);
		selected.clear();

		routeList.push_back(lineRouteList);
	}


	vector<Valve> result;

	for (size_t i = 0; i < lines.size(); i++) {
		
		Valve valve;

		valve.id = i;
		valve.flow = flowList[i];
		valve.name = nameList[i];

		for (size_t iR = 0; iR < routeList[i].size(); iR++) {
			valve.routes.push_back(findMatchingIndex(nameList , routeList[i][iR]));
		}

		
		cout << valve.id << ';' << valve.name << ';' << valve.flow << "f;" ;
		for (size_t iS = 0; iS < valve.routes.size(); iS++) {
			cout << valve.routes[iS] << ",";
		}
		cout << ';' << endl;
	
		result.push_back(valve);
	}

	
	return result;
}

vector<Valve> generateTestInput() {
	vector<Valve> result;
  for (int i = 0; i < 10; i++) {
		Valve valve;
		valve.id = i;
		valve.flow = rand() % 10 + 1;
		valve.name = "V" + to_string(i);
		valve.routes = {};
		result.push_back(valve);
	}
	for (Valve v : result) {
		for (int i = 0; i < rand() % 3 + 1; i++) {
			v.routes.push_back(rand() % 10);
		}
	}
	return result;
}

// Maximal weighted independent set
int mwis (vector<Valve> & graph, Valve & source, int remainingMinutes, int maxFlow, vector<Valve> & visited_path) {
	//TODO Add DP
	if (remainingMinutes == 0) {
		return maxFlow;
	}
	std::vector<Valve> neighbors = {};
	for (int i = 0; i < source.routes.size(); i++) {
		neighbors.push_back(graph[source.routes[i]]);
	}
	for (int i = 0; i < neighbors.size(); i++) {
		int temp = mwis(graph, neighbors[i], remainingMinutes - 1, maxFlow, visited_path);
		if (temp > maxFlow) {
			remainingMinutes--;
			maxFlow = temp;
		}
	}
	visited_path.push_back(source);
	return maxFlow + source.flow*remainingMinutes;
}

int main(){
	setInputs(0);

	//vector<Valve> testGraph = generateTestInput();

	vector <Valve> testGraph = sortInputFile();

	vector<Valve> visited_path = {};
	cout << mwis(testGraph, testGraph[0], 30, -1, visited_path) << endl;


	return 0;
}