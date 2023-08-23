#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <map>
#include <list>
#include <utility>
#include <queue>

using namespace std;

string inputName;

struct Valve{
	int id;
	string name;
	int flow;
	vector <int> routes;
};

struct Node {
	uint32_t id;
	uint32_t flow;
	bool isOpen;
	bool visited;
	uint32_t weight = -1;
	uint32_t path_length = -1;

	vector< pair< shared_ptr<Node>, bool >> neighbors;
	Node(uint32_t id, uint32_t flow, bool isOpen = false) : id(id), flow(flow), isOpen(isOpen) {
		neighbors = {};
	}
};
//TODO1 Create nodes from input
//TODO2 Create edges from input
//  - Create 2 edges from each node - one for open, one for closed
// Examples of creating shared pointers
// auto p = shared_ptr<Node>(new Node);
// shared_ptr<Node> p2 = make_shared<Node>(n1);
//TODO3 Traverse graph while keeping minutes using "Djikstra's algorithm" but for max flow




void setInputs(bool setCheck) {
	if (setCheck) {
		inputName = "true_input.txt";

	}
	else {
		inputName = "test_input.txt";

	}
}


int findMatchingIndex(const vector<string>& strings, const string& target) {
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

		valve.id = (int) i;
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

bool isVisitedOrOpen(list<pair<int, bool>> & visited_path, int id) {
	for(pair<int, bool> p : visited_path) {
		if (p.first == id) {
			return p.second;
		}
	}
	return false;
}


int maxDjikstra(vector<shared_ptr<Node>> & nodes, shared_ptr<Node> start) {
	// Initialization
	uint8_t minutes = 30;
	vector<shared_ptr<Node>> predecessors;
	start->weight = 0;
	start->path_length = 0;
	queue<shared_ptr<Node>> q;
	q.push(start);
	while(!q.empty()) {
		// Pop the first element
		shared_ptr<Node> current = q.front();
		q.pop();
		// Iterate through neighbors
		for (pair<shared_ptr<Node>, bool> neighbor : current->neighbors) {
			// If going through the "opening edge"
			if (neighbor.second) {
				// If current path is better than the previous one (weight with flow of destination node is less than current weight + minutes*current_flow)
				if (neighbor.first->weight < current->weight + minutes*current->flow && current->path_length < 30) {
					// Update the weight of the destination node
					neighbor.first->weight = current->weight + minutes*current->flow;
					// Save the predecessor
					predecessors.push_back(current);
					// Update the path length (minutes spent on the path)
					neighbor.first->path_length = current->path_length + 2;
					// Set the node as open to prevent opening the same node twice
					current->isOpen = true;
					// Push the node to the queue
					q.push(neighbor.first);
				}
			// If going through the "closing edge"	
			} else {
				// If current path is better than the previous one (weight of destination node is less than current weight)
				if (neighbor.first->weight < current->weight && current->path_length < 30) {
					// Update the weight of the destination node
					neighbor.first->weight = current->weight;
					// Save the predecessor
					predecessors.push_back(current);
					// Update the path length (minutes spent on the path)
					neighbor.first->path_length = current->path_length + 1;
					// NOT SETTING IS OPEN, SINCE WE JUST "VISITED" THE NODE, NOT OPENED IT
					// Push the node to the queue
					q.push(neighbor.first);
				}
			}
		}
	}
	// Find the node with the highest weight
	shared_ptr<Node> maxNode;
	for (shared_ptr<Node> node : nodes) {
		if (node->weight > maxNode->weight) {
			maxNode = node;
		}
	}
	// Return the result
	return maxNode->weight;
	//TODO return also predecessors and use them to reconstruct the path (go through predecessors until you reach the start node) P.S. Fakt nevim jestli vector predchudcu bude fungovat kvuli moznym cyklum
	// P.S. 2: Kouknul bych se na jine algoritmy a zpusoby rekonstrukce cesty pro grafy s cyklickymi cestami
}

//Convert valve vector to node vector
vector<shared_ptr<Node>> valveToNode(vector<Valve> & valve_vector) {
	vector<shared_ptr<Node>> result_vector = {};
	// Create nodes
	for (Valve valve : valve_vector) {
		shared_ptr<Node> n = make_shared<Node>(Node(valve.id, valve.flow));
		result_vector.push_back(n);
	}
	// Add the neighbors (one edge for closed, one for open)
	for (size_t i = 0; i < valve_vector.size(); i++) {
		Valve valve = valve_vector[i];
		for(size_t j = 0; j < valve.routes.size(); j++) {
			result_vector[i]->neighbors.push_back({result_vector[valve.routes[j]], true});
			result_vector[i]->neighbors.push_back({result_vector[valve.routes[j]], false}); // jsem dement, dal jsem tam {} xd
		}
	}
	return result_vector;
}

int main(){
	setInputs(0); // Musim pracovat, ale doma bych se kouknul jak vypada ten node graph, jestli se spravne nacetl
	//na další task si to m?síme víc rozplánovat protože já nemám tušení co tv?j kód upln? d?la //yes, zkusím okomentovat, nebo spis pak na discordu// cool with me?? :D
	//vector<Valve> testGraph = generateTestInput();

	vector <Valve> testGraph = sortInputFile();
	vector <shared_ptr<Node>> node_vector = valveToNode(testGraph);
	shared_ptr<Node> start_node;
  for (shared_ptr<Node> node : node_vector) {d
		if (node->id == testGraph[0].id) {
			start_node = node;
		}
	}

	cout << maxDjikstra(node_vector, start_node) << endl;

	return 0;
}
