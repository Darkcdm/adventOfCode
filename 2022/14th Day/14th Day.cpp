// 14th Day.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <string>


using namespace std;

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

/*
struct simPlace {
	Cell** cells;
	int depth;
	int width; 

	simPlace() {
		this->cells = (Cell**) calloc(1, sizeof(Cell*));
		this->cells[0] = (Cell*)calloc(1, sizeof(Cell));
	
		this->depth = 1;
		this->depth = 1;
	}

	void reserveWidth(int index, int order) {
		
	}
	void reserveDepth(int order) {
		this->cells = (Cell**)realloc(this->cells, order);
	}

	void kill() {
		for (int y = 0; y < this->depth; y++) {
			free(this->cells[y]);
		}
		free(this->cells);
	}
};
*/


//returns Top Left and Bottom Right Coords
vector<int> parseDimension() {
	vector<int> results;

	ifstream input;
	input.open("input.txt");

	string line;

	while (getline(input, line)) {
		int leftIndex = 0;
		int rightIndex = 0;

		while (rightIndex != line.size()) {
			leftIndex = rightIndex;
			rightIndex = (int) line.find(' ', leftIndex + 1);

			if (rightIndex == -1) {
				rightIndex = (int)line.size();
			}

			string coords = line.substr(leftIndex, rightIndex - leftIndex);

			if (coords[1] == '-') {
				leftIndex = rightIndex;
				rightIndex = (int) line.find(' ', leftIndex + 1);

				if (rightIndex == -1) {
					rightIndex = (int) line.size();
				}

				coords = line.substr(leftIndex, rightIndex - leftIndex);
			}

			string strX = coords.substr(0, coords.find(','));
			string strY = coords.substr(coords.find(',') + 1);

			int x = stoi(strX);
			int y = stoi(strY);

			if (results.empty()) {
				results.push_back(x);
				results.push_back(y);
				results.push_back(x);
				results.push_back(y);
			}

			if (x < results[0]) {
				results[0] = x;
			}
			if (y < results[1]) {
				results[1] = y;
			}
			if (x > results[2]) {
				results[2] = x;
			}
			if (y > results[3]) {
				results[3] = y;
			}


		}
	}

	input.close();

	return results;
}

void printCave(vector<vector<Cell>> cave) {
	for (int y = 0; y < cave.size(); y++) {
		for (int x = 0; x < cave[y].size(); x++) {
			cout << cave[y][x].symbol;
		}
		cout << endl;
	}
}

vector<vector<Cell>> createCave(int depth, int width, int leftX) {
	vector<vector<Cell>> result (depth, vector<Cell>(width));

	//result.resize(depth);
	//result.reserve((size_t) depth);
	

	

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






	
	ifstream input;
	string line;
	input.open("input.txt");






	//parse Lines
	while (getline(input, line)) {
		int leftIndex = 0;
		int rightIndex = 0;

		vector<int> points;
		points.resize(4);

		leftIndex = rightIndex;
		rightIndex = (int)line.find(' ', leftIndex + 1);

		//fix shit if you're at the end
		if (rightIndex == -1) {
			rightIndex = (int)line.size();
		}

		string coords = line.substr(leftIndex, rightIndex - leftIndex);

		//if you're in the middle then cross out the arrow
		if (coords[1] == '-') {
			leftIndex = rightIndex;
			rightIndex = (int)line.find(' ', leftIndex + 1);

			if (rightIndex == -1) {
				rightIndex = (int) line.size();
			}

			coords = line.substr(leftIndex, rightIndex - leftIndex);
		}

		//parse the strings into numbers
		string strX = coords.substr(0, coords.find(','));
		string strY = coords.substr(coords.find(',') + 1);

		points[2] = stoi(strX);
		points[3] = stoi(strY);






		//go untill you reach the end of the file
		while (rightIndex != line.size()) {
			points[0] = points[2];
			points[1] = points[3];

			leftIndex = rightIndex;
			rightIndex = (int)line.find(' ', leftIndex + 1);

			//fix shit if you're at the end
			if (rightIndex == -1) {
				rightIndex = (int)line.size();
			}

			coords = line.substr(leftIndex, rightIndex - leftIndex);

			//if you're in the middle then cross out the arrow
			if (coords[1] == '-') {
				leftIndex = rightIndex;
				rightIndex = (int)line.find(' ', leftIndex + 1);

				if (rightIndex == -1) {
					rightIndex = (int)line.size();
				}

				coords = line.substr(leftIndex, rightIndex - leftIndex);
			}

			//parse the strings into numbers
			strX = coords.substr(0, coords.find(','));
			strY = coords.substr(coords.find(',') + 1);
			points[2] = stoi(strX);
			points[3] = stoi(strY);

			//do something with parsed values
			//...

			vector<int> paintVector = {points[0]+points[2], points[1]+points[3]};

			for (int x = 0; x < paintVector[0]; x++) {
				result[points[1]][points[0] + x].solid = true;
				result[points[1]][points[0] + x].symbol = '#';

			}
			for (int y = 0; y < paintVector[1]; y++) {
				result[points[1] + y][points[0]].solid = true;
				result[points[1] + y][points[0]].symbol = '#';
			}
		}
	}

	input.close();
	

	return result;

}

int main() {
	vector<int> dimensions = parseDimension();

	vector<vector<Cell>> cave = createCave(dimensions[3], dimensions[2] - dimensions[0] + 2, dimensions[0] - 1);

	cout << dimensions[0] << ", ";
	cout << dimensions[1] << ", ";

	cout << dimensions[2] << ", ";
	cout << dimensions[3] << ", ";
	cout << endl;

	printCave(cave);
}