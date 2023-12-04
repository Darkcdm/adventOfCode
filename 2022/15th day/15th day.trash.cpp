#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;
string input_str = "input.txt";

struct Cast {
    int radius;
    int Xcenter;
    int Ycenter;
    int Xradius;
    int Yradius;

    void setRadius() {
        int deltaX = abs(Xcenter - Xradius);
        int deltaY = abs(Ycenter - Yradius);
        radius = deltaX + deltaY;
    }
};

struct Cell {
    int X;
    int Y;
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


bool checkDuplicates(vector <Cell> list, int x, int y) {

    for (size_t i = 0; i < list.size(); i++) {
        if (list[i].X == x && list[i].Y == y) {
            return true;
        }
    }
    return false;
}

vector<Cell> countIntersectCell(vector <Cast> allCasts, int checkLine) {
    vector<Cell> count;

    for (size_t index = 0; index < allCasts.size(); index++) {
        Cast circle = allCasts[index];
    

        for (int x = circle.Xcenter - circle.Xradius; x <= circle.Xcenter + circle.Xradius; ++x) {
            for (int y = circle.Ycenter - circle.Yradius; y <= circle.Ycenter + circle.Yradius; ++y) {
                if (y == checkLine) {
                    if (!checkDuplicates(count, x, y)) {
                        Cell newCell;
                        newCell.X = x;
                        newCell.Y = y;
                        count.push_back(newCell);
                    }
                }
            }
        }
    }
    return count;
    
}

int main(){

    vector<Cell> result;

    vector <Cast> allCasts = loadCircles();
    result = countIntersectCell(allCasts, 10);


    for (size_t i = 0; i < result.size(); i++) {
        cout << "[" << result[i].X << ", " << result[i].Y << "]" << endl;
    }

    cout << endl << endl << result.size();
}

