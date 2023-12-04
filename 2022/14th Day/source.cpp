
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

string input_str = "input.txt";

struct Cell {
	int x;
	int y;
	int trueX;
	int trueY;

	bool occupied;
	bool solid;
	char symbol;
	bool source;

	Cell(int x, int y, int trueX, int trueY) {
		this->x = x;
		this->y = y;
		this->trueX = trueX;
		this->trueY = trueY;

		occupied = false;
		solid = false;
		source = false;
		symbol = '.';
	}
};

int getCoords(string line, string& coords, size_t& leftIndex, size_t& rightIndex) {
	
	if (rightIndex >= line.size()) {
		return 0;
	}
	
	leftIndex = rightIndex;
	rightIndex = line.find(' ', leftIndex + 1);

	if (rightIndex == -1) {
		rightIndex = line.size();
	}

	coords = line.substr(leftIndex, rightIndex - leftIndex);

	if (coords[1] == '-') {
		return getCoords(line, coords, leftIndex, rightIndex);
	}

	
	return 1;
}

vector<int> parseCoords(string coords) {
	vector<int> result;

	result.push_back(stoi(coords.substr(0, coords.find(','))));
	result.push_back(stoi(coords.substr(coords.find(',') + 1)));

	return result;
}

vector<int> parseDimension() {
	ifstream input;
	input.open(input_str);

	vector<int> results;
	


	string line;
	while(getline(input, line)) {
		size_t leftIndex = 0;
		size_t rightIndex = 0;
		string coordStr;

		while (getCoords(line, coordStr, leftIndex, rightIndex)) {
			vector <int> coords = parseCoords(coordStr);

			if (results.size() == 0) {
				results.push_back(coords[0]);
				results.push_back(coords[1]);
				results.push_back(coords[0]);
				results.push_back(coords[1]);
			}

			if (coords[0] < results[0]) {
				results[0] = coords[0];
			}
			if (coords[1] < results[1]) {
				results[1] = coords[1];
			}
			if (coords[0] > results[2]) {
				results[2] = coords[0];
			}
			if (coords[1] > results[3]) {
				results[3] = coords[1];
			}
		}
	}



	input.close();

	return results;
}

vector<vector<Cell>> createCave(vector<int> coords) {

	vector<vector<Cell>> result;

	int depth = coords[3] + 2;
	int width = coords[2] - coords[0] + 1000;
	int leftX = coords[0] - 500;

	

	//create the space
	for (int y = 0; y < depth; y++) {
		vector<Cell> line;
		for (int x = 0; x < width; x++) {


			Cell newCell(x, y, leftX + x, y);
			//place source
			if (leftX + x == 500 && y == 0) {
				newCell.source = true;
				newCell.symbol = '+';
			}

			line.push_back(newCell);
		}
		result.push_back(line);
	}

	return result;
}

void printCave(vector<vector<Cell>> cave) {

	cout << endl << "   |";

	for (size_t x = 0; x < cave[0].size(); x++) {
		cout << x;
	}

	cout << endl;

	for (size_t index = 0; index < to_string(cave[0][0].trueX).size(); index++) {
		cout << "   |";
		for (size_t x = 0; x < cave[0].size(); x++) {
			cout << to_string(cave[0][x].trueX)[index];
		}
		cout << endl;
	}

	cout << "---+";
	for (size_t x = 0; x < cave[0].size(); x++) {
		cout << "-";
	}
	cout << endl;

	for (size_t y = 0; y < cave.size(); y++) {
		int spacer = 2;
		if (y > 9) {
			spacer--;
		}
		if (y > 99) {
			spacer--;
		}
		
		for (int i = 0; i < spacer; i++) {
			cout << ' ';
		}

		cout << y << '|';
		for (size_t x = 0; x < cave[y].size(); x++) {
			cout << cave[y][x].symbol;
		}
		cout << endl;
	}
}

void addObsticles(vector<vector<Cell>>& cave, vector<int> dimensions) {
	string line;
	ifstream input;
	input.open(input_str);

	int maxLeftX = cave[0][0].trueX;


	while (getline(input, line)){
		
		size_t leftIndex = 0;
		size_t rightIndex = 0;
		string coordStr;

		vector<int> newCoords;
		vector<int> oldCoords;


		while (getCoords(line, coordStr, leftIndex, rightIndex)) {
			oldCoords = newCoords;
			newCoords = parseCoords(coordStr);

			if (oldCoords.size() == 0) {
				continue;
			}
			vector<int> obstacleVector;
			obstacleVector.push_back(newCoords[0] - oldCoords[0]);
			obstacleVector.push_back(newCoords[1] - oldCoords[1]);

			if (obstacleVector[0] != 0) {
				int y = oldCoords[1];
				int changeValue;
				if (obstacleVector[0] < 0) {
					changeValue = -1;
				}
				else {
					changeValue = 1;
				}

				for (int helpX = 0; helpX != obstacleVector[0] + changeValue; helpX = helpX + changeValue) {
					
					int focusedX = oldCoords[0] + helpX - maxLeftX;

					cave[y][focusedX].occupied = true;
					cave[y][focusedX].solid = true;
					cave[y][focusedX].symbol = '#';
				
				}
			} else if (obstacleVector[1] != 0) {
				int x = oldCoords[0]- maxLeftX;
				int changeValue;
				if (obstacleVector[1] < 0) {
					changeValue = -1;
				}
				else {
					changeValue = 1;
				}

				for (int helpY = 0; helpY != obstacleVector[1] + changeValue; helpY = helpY + changeValue) {
					int focusedY = oldCoords[1] + helpY;

					cave[focusedY][x].occupied = true;
					cave[focusedY][x].solid = true;
					cave[focusedY][x].symbol = '#';

				}



			}
		}
	}

	input.close();
}

int simulateVoid(vector<vector<Cell>> &cave) {
	int sandCounter = 0;
	cout << endl;

	int spawnerX = 0;
	int spawnerY = 0;

	for (size_t y = 0; y < cave.size(); y++) {
		for (size_t x = 0; x < cave[0].size(); x++) {
			if (cave[y][x].source) {
				spawnerX = x;
				spawnerY = y;
			}
		}
	}

	while (sandCounter < cave.size()*cave[0].size()){
		//cout << sandCounter << endl;
		//spawn
		sandCounter++;
		
		int sandX = spawnerX;
		int sandY = spawnerY;





		while (true) {
			//check Borders
			//check Space and Fall
				//DOWN
			if (sandY + 1 >= cave.size()) {
				return sandCounter;
			}
			if (!cave[sandY + 1][sandX].occupied) {
				sandY++;
				continue;
			}

			//LEFT
			if (sandX - 1 < 0) {
				return sandCounter;
			}
			if (!cave[sandY + 1][sandX - 1].occupied) {
				sandY++;
				sandX--;
				continue;
			}

			//RIGHT
			if (sandX + 1 >= cave[0].size()) {
				return sandCounter;
			}
			if (!cave[sandY + 1][sandX + 1].occupied) {
				sandY++;
				sandX++;
				continue;
			}

			//stay
			cave[sandY][sandX].occupied = true;
			cave[sandY][sandX].symbol = '0';

			break;
		}
	}
	return sandCounter;
}

int simulateFloor(vector<vector<Cell>>& cave) {
	int sandCounter = 0;
	cout << endl;

	int spawnerX = 0;
	int spawnerY = 0;

	for (size_t y = 0; y < cave.size(); y++) {
		for (size_t x = 0; x < cave[0].size(); x++) {
			if (cave[y][x].source) {
				spawnerX = x;
				spawnerY = y;
			}
		}
	}

	while (sandCounter < cave.size() * cave[0].size()) {
		//cout << sandCounter << endl;
		//spawn
		sandCounter++;

		int sandX = spawnerX;
		int sandY = spawnerY;





		while (true) {
			//check Borders
			//check Space and Fall
				//DOWN
			if (sandY + 1 >= cave.size()) {
				cave[sandY][sandX].occupied = true;
				cave[sandY][sandX].symbol = '0';

				break;
			}
			if (!cave[sandY + 1][sandX].occupied) {
				sandY++;
				continue;
			}

			//LEFT
			if (sandX - 1 < 0) {
				return -1;
			}
			if (!cave[sandY + 1][sandX - 1].occupied) {
				sandY++;
				sandX--;
				continue;
			}

			//RIGHT
			if (sandX + 1 >= cave[0].size()) {
				return -1;
			}
			if (!cave[sandY + 1][sandX + 1].occupied) {
				sandY++;
				sandX++;
				continue;
			}
			
			if (sandX == spawnerX && sandY == spawnerY) {
				return sandCounter;
			}


			//stay
			cave[sandY][sandX].occupied = true;
			cave[sandY][sandX].symbol = '0';

			break;
		}
	}
	return -2;
}


int main() {
	vector<int> dimensions = parseDimension();

	vector<vector<Cell>> cave = createCave(dimensions);

	addObsticles(cave, dimensions);

	cout << "Dimensions are: [" << dimensions[0] << ", " << dimensions[1] << "],[" << dimensions[2] << ", " << dimensions[3] << "]" << endl << endl;
	/*
	cout << dimensions[0] << ", ";
	cout << dimensions[1] << ", ";

	cout << dimensions[2] << ", ";
	cout << dimensions[3] << ", ";
	cout << endl;
	*/

	int result = simulateFloor(cave);
	if (result == -1) {
		cout << "ran out of space";
	}else if (result == -2){
		cout << "Something went wrong";
	}
	else {
		cout << "Result is: " << result;
	}


	//printCave(cave);
}