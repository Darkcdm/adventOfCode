#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <limits.h>

using namespace std;



struct Cell {
	char symbol;
	int height;
	int X;
	int Y;
	
};

struct Path {
	Cell* destination;
	int weight;
};

struct Node {
	Cell cell;
	Path* paths;
	int pathCount;
	int distance;
	bool visited;
};

struct DataSet {
	int height;
	int width;
	Node** nodes;
	Node* Start;
	Node* End;
	Cell* possibleStarts;
	int possibleStartsCount;

	void init() {
		ifstream input;
		input.open("input.txt");

		string line;

		getline(input, line);
		this->width = (int) line.size();

		int count = 1;
		while (getline(input,line)) {
			count++;
		}
		this->height = count;

		input.close();
	
		this->nodes = (Node**)calloc(this->height, sizeof(Node*));

		for (int i = 0; i < this->height; i++) {
			this->nodes[i] = (Node*)calloc(this->width, sizeof(Node));
		}
	}
	
	void fill() {
		ifstream input;
		input.open("input.txt");
		string line;


		int y = 0;
		while (getline(input, line)) {
			for (int x = 0; x < this->width; x++) {
				this->nodes[y][x].cell.symbol = line[x];
			}
			y++;
		}
		input.close();

		for (int y = 0; y < this->height; y++) {
			for (int x = 0; x < this->width; x++) {
				this->nodes[y][x].distance = INT_MAX;

				this->nodes[y][x].cell.height = getHight(this->nodes[y][x].cell.symbol);
				this->nodes[y][x].cell.X = x;
				this->nodes[y][x].cell.Y = y;

				if (this->nodes[y][x].cell.symbol == 'S') {
					this->Start = &this->nodes[y][x];
					this->nodes[y][x].distance = 0;
				}
				if (this->nodes[y][x].cell.symbol == 'E') {
					this->End = &this->nodes[y][x];
				}

				this->nodes[y][x].visited = false;
			}
		}

		for (int y = 0; y < this->height; y++) {
			for (int x = 0; x < this->width; x++) {
				this->nodes[y][x].paths = (Path*)calloc(4, sizeof(Path));
				this->nodes[y][x].pathCount = 0;
				//check N
				if (y != 0) {
					this->checkPath(&this->nodes[y][x], &this->nodes[y - 1][x]);
				}
				//check S
				if (y != this->height-1) {
					this->checkPath(&this->nodes[y][x], &this->nodes[y + 1][x]);
				}
				//check E
				if (x != 0) {
					this->checkPath(&this->nodes[y][x], &this->nodes[y][x - 1]);
				}
				//check W
				if (x != this->width-1) {
					this->checkPath(&this->nodes[y][x], &this->nodes[y][x + 1]);
				}
				this->nodes[y][x].paths = (Path*)realloc(this->nodes[y][x].paths, sizeof(Path)* this->nodes[y][x].pathCount);
			}
		}
		
	}

	/*
	returns the wight of the path if there is any
	0 if it's going down
	1 if it's going up
	-1 if the path doesn't exists
	*/
	void checkPath(Node* currentNode, Node* checkedNode) {
		if (checkedNode->cell.height <= currentNode->cell.height + 1) {
			createPath(currentNode, &checkedNode->cell, 1);
		}

	}

	void createPath(Node * node, Cell * destination, int weight) {
		node->paths[node->pathCount].destination = destination;
		node->paths[node->pathCount].weight = weight;
		node->pathCount++;
	}

	int getHight(char symbol) {
		if (symbol == 'S') {
			return 0;
		}
		if (symbol == 'E') {
			return 25;
		}

		return (int)symbol - 97;
	}

	void printHeight() {
		for (int y = 0; y < this->height; y++) {
			for (int x = 0; x < this->width; x++) {
				cout << this->nodes[y][x].cell.height << " ";
			}
			cout << endl;
		}
	}

	void printSymbols() {
		for (int y = 0; y < this->height; y++) {
			for (int x = 0; x < this->width; x++) {
				cout << this->nodes[y][x].cell.symbol;
			}
			cout << endl;
		}
	}

	void printPaths() {
		for (int y = 0; y < this->height; y++) {
			for (int x = 0; x < this->width; x++) {
			
				for(int i = 0; i < this->nodes[y][x].pathCount; i++){
				cout << this->nodes[y][x].cell.symbol << '-' << this->nodes[y][x].cell.height;
				cout << '(' << this->nodes[y][x].cell.X << ", " << this->nodes[y][x].cell.Y << ')';
				cout << " --> ";
				cout << this->nodes[y][x].paths[i].destination->symbol << '-' << this->nodes[y][x].paths[i].destination->height;
				cout << '(' << this->nodes[y][x].paths[i].destination->X << ", " << this->nodes[y][x].paths[i].destination->Y << ')';
				cout << endl;
				}
				cout << endl;
			}
		}
	}

	int dijkstra() {
		int vorticiesCount = this->width * this->height;

		while (vorticiesCount > this->countVisited()) {
			//this->printVisited();

			Node* selectedNode = this->findShortest();

			if (this->countVisited() == 7065) {
				//this->printVisited();
			}

			if (selectedNode == NULL) {
				cout << "ERROR" << endl;
				cout << "Last known shortest distance is: " << this->End->distance << endl;
				return this->End->distance;
			}
			selectedNode->visited = true;

			for (int i = 0; i < selectedNode->pathCount; i++) {
				Cell routeCell = *selectedNode->paths[i].destination;
				Node* routeNode = &this->nodes[routeCell.Y][routeCell.X];
			
				routeNode->distance = selectedNode->distance + selectedNode->paths[i].weight;
			}

		}
		cout << "ROUTE LENGTH: " << this->End->distance << endl;
		return this->End->distance;
	}

	Node* findShortest() {
		Node* shortest = NULL;
		int minDistance = INT_MAX;

		for (int y = 0; y < this->height; y++) {
			for (int x = 0; x < this->width; x++) {
				int currentDistance = this->nodes[y][x].distance;
				if (currentDistance < minDistance && !this->nodes[y][x].visited) {
					minDistance = currentDistance;
					shortest = &this->nodes[y][x];
				}
			}
		}

		return shortest;
	}

	int countVisited() {
		int count = 0;
		for (int y = 0; y < this->height; y++) {
			for (int x = 0; x < this->width; x++) {
				if (this->nodes[y][x].visited) {
					count++;
				}
			}
		}
		return count;
	}

	void printVisited() {
		for (int y = 0; y < this->height; y++) {
			for (int x = 0; x < this->width; x++) {
				if (this->nodes[y][x].visited) {
					cout << '*';
				}
				else {
					cout << '.';
				}
				
			}
			cout << endl;
		}
		cout << endl;

	}

	void resetNodes() {
		for (int y = 0; y < this->height; y++) {
			for (int x = 0; x < this->width; x++) {
				this->nodes[y][x].distance = INT_MAX;
				this->nodes[y][x].visited = false;
			}
		}

		this->Start->distance = 0;
	}

	void setPossibleStarts() {
		this->possibleStartsCount = 0;

		for (int y = 0; y < this->height; y++) {
			for (int x = 0; x < this->width; x++) {
				if (this->nodes[y][x].cell.height == 0) {
					this->possibleStartsCount++;
				}
			}
		}
			this->possibleStarts = (Cell*) calloc(this->possibleStartsCount, sizeof(Cell));
			int index = 0;

		for (int y = 0; y < this->height; y++) {
			for (int x = 0; x < this->width; x++) {
				if (this->nodes[y][x].cell.height == 0) {
					this->possibleStarts[index] = this->nodes[y][x].cell;

					index++;
				}
			}
		}
	}
};




int main() {
	DataSet data;
	data.init();
	data.fill();

	cout << "Width: " << data.width << endl;
	cout << "Height: " << data.height << endl;
	/*
	data.printSymbols();
	cout << endl;
	data.printHeight();
	cout << endl;
	data.printPaths();
	*/
	data.setPossibleStarts();

	int* distArr = (int*)calloc(data.possibleStartsCount, sizeof(int));

	for (int i = 0; i < data.possibleStartsCount; i++) {
		Cell* startingCell = &data.possibleStarts[i];
		data.Start = &data.nodes[startingCell->Y][startingCell->X];

		data.resetNodes();
		distArr[i] = data.dijkstra();
	}
	
	int smolDist = INT_MAX;
	for (int i = 0; i < data.possibleStartsCount; i++) {

		if (distArr[i] < smolDist) {
			smolDist = distArr[i];
		}
	}

	cout << "Smallest distance is: " << smolDist;
}