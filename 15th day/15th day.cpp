#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <unordered_set>

using namespace std;
string input_str = "input.txt";

size_t maxCellCount;

struct Cast {
    long long int radius;
    long long int Xcenter;
    long long int Ycenter;
    long long int Xradius;
    long long int Yradius;

    void setRadius() {
        long long int deltaX = abs(Xcenter - Xradius);
        long long int deltaY = abs(Ycenter - Yradius);
        radius = deltaX + deltaY;
    }
};

struct Cell {
    long long int X;
    long long int Y;
};


vector <Cast> loadCircles() {
    vector <Cast> out;

    ifstream inputFile;

    inputFile.open(input_str);

    string input;
    while (getline(inputFile, input)) {
        size_t cursor = 0;
        Cast circle;

        // Parse the Sensor's X and Y
        size_t sensor_x_pos = input.find("Sensor at x=");
        size_t sensor_y_pos = input.find(", y=");

        if (sensor_x_pos != std::string::npos && sensor_y_pos != std::string::npos) {
            std::string sensor_x_str = input.substr(sensor_x_pos + 12, sensor_y_pos - sensor_x_pos - 12);
            std::string sensor_y_str = input.substr(sensor_y_pos + 4);

            circle.Xcenter = stoi(sensor_x_str);
            circle.Ycenter = stoi(sensor_y_str);
        }

        // Parse the Beacon's X and Y
        size_t beacon_x_pos = input.find("x=", sensor_y_pos);
        size_t beacon_y_pos = input.find(", y=", beacon_x_pos);

        if (beacon_x_pos != std::string::npos && beacon_y_pos != std::string::npos) {
            std::string beacon_x_str = input.substr(beacon_x_pos + 2, beacon_y_pos - beacon_x_pos - 2);
            std::string beacon_y_str = input.substr(beacon_y_pos + 4);
            circle.Xradius = stoi(beacon_x_str);
            circle.Yradius = stoi(beacon_y_str);
        }


        circle.setRadius();

        out.push_back(circle);
    }

    inputFile.close();
    return out;
}


bool checkDuplicates(vector <Cell> list, long long int x, long long int y) {

    for (size_t i = 0; i < list.size(); i++) {
        if (list[i].X == x && list[i].Y == y) {
            return true;
        }
    }
    return false;
}

vector<Cell> getIntersectCell(vector <Cast> allCasts, long long int checkLine) {
    vector<Cell> count;

    for (size_t index = 0; index < allCasts.size(); index++) {
        Cast circle = allCasts[index];


        long long int delta = abs(circle.Ycenter - checkLine);
        long long int maxWidth = circle.radius * 2 + 1;
        long long int deltaWidth = delta * 2;
        long long int lineWidth = maxWidth - deltaWidth;

        for (long long int x = circle.Xcenter - lineWidth / 2; x < circle.Xcenter + lineWidth / 2 + 1; x++) {


            Cell newCell;
            newCell.X = x;
            newCell.Y = checkLine;
            count.push_back(newCell);

                

                if (count.size() > maxCellCount) {
                    count.clear();
                    return count;
                }
        }
    }
    return count;

}

vector<Cell> removeBeacons(vector <Cell> cellList, vector<Cast> casts) {
    vector<Cell> newList;

    for (size_t index = 0; index < cellList.size(); index++) {
        bool clear = true;

        for (size_t castIndex = 0; castIndex < casts.size(); castIndex++) {
            if (casts[castIndex].Yradius != cellList[index].Y) {
                continue;
            }
            
            if (casts[castIndex].Xradius == cellList[index].X) {
                clear = false;
                break;
            }
        }

        if (clear) {
            newList.push_back(cellList[index]);
        }
    }



    return newList;
}

bool checkIntersect(Cast circle,int line) {

    if (circle.Ycenter + circle.radius + 1 >= line && circle.Ycenter - circle.radius + 1 <= line) {
        return true;
    }


    return false;
}

vector <Cast> getSmallerList(vector <Cast> casts, int line) {
    vector <Cast> result;

    for (size_t i = 0; i < casts.size(); i++) {
        if (checkIntersect(casts[i], line) ){
            result.push_back(casts[i]);
        }
    }

    return result;
}

void printCircleParams(vector <Cast> allCasts, int line) {
    maxCellCount = 0;
    
    cout << "Printing Params: " << endl;

    for (size_t i = 0; i < allCasts.size(); i++) {
        Cast circle = allCasts[i];
        cout << "[" << circle.Xcenter << ", " << circle.Ycenter << "] <--> ";
        cout << circle.radius << "...";
        cout << "[" << circle.Xradius << ", " << circle.Yradius << "] : ";
        cout << checkIntersect(circle ,line) << " : ";
        cout << circle.radius * 2 + 1;

        cout << endl;

        maxCellCount = maxCellCount + circle.radius * 2 + 1;
    }

    cout << "Max cell Count :" << maxCellCount;
    cout << endl;
}

bool compareCells(const Cell& a, const Cell& b) {
    return (a.X < b.X);
}

vector<Cell> removeDuplicates(std::vector<Cell>& list) {
    vector<Cell> newList;
    cout << "sorting \n";
    sort(list.begin(), list.end(), compareCells);

    long long int oldX = list[0].X - 1;
    float percentDoneOld = -1;
    for (size_t i = 0; i < list.size(); i++) {
        if (list[i].X == oldX) {
            //list.erase(list.begin() + i);
        }
        else {
            newList.push_back(list[i]);
            oldX = list[i].X;
        }
        
        



        float percentDoneNew = static_cast<float>(i) / (list.size() / 100.0);
        percentDoneNew = round(percentDoneNew);
        if (percentDoneOld != percentDoneNew) {
            cout << percentDoneNew << endl;
            percentDoneOld = percentDoneNew;
         }
        
    }
    return newList;
}

int main() {

    int selectedLine = 2000000;

    vector<Cell> result;
    cout << "Loading Circles" << endl;
    vector <Cast> allCasts = loadCircles();
    printCircleParams(allCasts, selectedLine);

    vector <Cast> smallerCasts;

    smallerCasts = getSmallerList(allCasts, selectedLine);


    printCircleParams(smallerCasts, selectedLine);

    cout << "Getting Intersects" << endl;
    result = getIntersectCell(smallerCasts, selectedLine);

    if (result.size() == 0) {
        return -1;
    }

    cout << "Got " << result.size() << " cells. Removing Duplicates." << endl;
    result = removeDuplicates(result);

    cout << "Got " << result.size() << " cells. Removing Beacons." << endl;
    result = removeBeacons(result, allCasts);

    cout << "result is: " << result.size() << endl;
}

