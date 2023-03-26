#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <limits.h>
#include <vector>
#include <sstream>

using namespace std;

struct Set {
    vector<int> values;
    vector<Set> sets;
};

Set parseLine(const std::string& input) {
    Set result;

    std::stringstream ss(input);
    char c;
    ss >> c; // Read the opening '['

    while (ss >> c && c != ']') {
        if (c == '[') {
            // Parse a sub-set
            ss.seekg(static_cast<long>(ss.tellg()) - 1);
            std::string subset_str;
            std::getline(ss, subset_str, ']');
            subset_str += ']';
            Set subset = parseLine(subset_str);
            result.sets.push_back(subset);
        }
        else if (isdigit(c)) {
            // Parse an integer value
            ss.seekg(static_cast<long>(ss.tellg()) - 1);
            int value;
            ss >> value;
            result.values.push_back(value);
        }
    }

    if (ss.good()) {
        // Read any remaining characters in the stringstream
        while (ss >> c) {
            if (isdigit(c)) {
                // Parse an integer value
                ss.seekg(static_cast<long>(ss.tellg()) - 1);
                int value;
                ss >> value;
                result.values.push_back(value);
            }
        }
    }

    return result;
}

void printSet(const Set& set) {
    // Print the values vector
    std::cout << "[";
    for (size_t i = 0; i < set.values.size(); ++i) {
        std::cout << set.values[i];
        if (i < set.values.size() - 1) {
            std::cout << ",";
        }
    }

    for (int i = 0; i < set.sets.size(); i++) {
        printSet(set.sets[i]);
    }

    std::cout << "]";

}

int countValuesInSet(Set set) {
    int count = (int) set.values.size();

    for (int i = 0; i < set.sets.size(); i++) {
        count = count + countValuesInSet(set.sets[i]);
    }
    return count;
}

bool compareSets(Set left, Set right) {

    

    for (int i = 0; i < left.values.size(); i++) {
        if (right.values.size() < i) {
            return false;
        }
        
        if (left.values[i] < right.values[i]) {
            return true;
        }
    }

    return true;
}

int main() {
    ifstream input;
    input.open("input.txt");

    vector<Set> sets;

    string line;
    while (getline(input,line)) {
        if(line.size()>0){
            sets.push_back(parseLine(line));
        }
    }
    input.close();

    int pairIndex = 0;
    int solution = 0;
    
    for (int i = 0; i < sets.size(); i = i + 2) {
        pairIndex++;

        Set left = sets[i];
        Set right = sets[i + 1];

        if (compareSets(left, right)) {
            solution = solution + pairIndex;
        }

        cout << pairIndex << " : " << solution << endl;
        printSet(sets[i]);
        cout << " : " << countValuesInSet(sets[i]) << endl;
        printSet(sets[i + 1]);
        cout << " : " << countValuesInSet(sets[i+1]) << endl;



        /*
        if (compareSets(left, right)) {
            solution = solution + pairIndex;
        }
        */
    }
    
    cout << "Solution is: " << solution << endl;

    return 0;
}
