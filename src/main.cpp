#include "../include/problem.h"
#include "../include/node.h"
#include "../include/search.h"

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

int main () {
    int input = 0;
    int algo = 0;
    Problem eightPuzzle; //default

    vector <vector <int> > inputState(3, vector<int>(3, 0));

    cout << "Welcome to XXX 8 puzzle solver." << endl;

    while (input != 1 && input != 2) {
        cout << "Type '1' to use default puzzle or '2' to enter your own puzzle." << endl;
        cin >> input;
    }

    if (input == 2) {
        cout << "Enter your puzzle." << endl << "Format for each row should be 'x y z', space inbetween each number. "
            << "Use '0' to represent a blank." << endl;

        cin.ignore();

        //input here NEEDED
        string line;
        for (int i = 0; i < 3; ++i) {
            getline(cin, line); // Read a line of input
            stringstream ss(line); // Create a string stream from the line

            for (int j = 0; j < 3; ++j) {
                ss >> inputState[i][j]; // Read integers into the grid
            }
        }

        eightPuzzle.setUserState(inputState);
    }

    //Algorithm Choice 
    cout << "Enter choice of algorithm. (Enter in Number)" << endl 
        << "Uniform Cost Search (1)" << endl
        << "A* with the Misplaced Tile heuristic (2)" << endl
        << "A* with the Euclidean distance heuristic (3)" << endl;

    cin >> algo;

    switch (algo) {
        case 1:     
            //call function 1 here
            cout << "func 1";
            break;
        case 2:
            //call function 1 here
            cout << "func2";
            break;
        case 3:
            //call function 1 here
            cout << "func 3";
            break;
        default: 
            cout << "Enter valid number for corresponding algorithm: 1 or 2 or 3" << endl;
    }

    for (auto &x: inputState) {
        for (auto &y : x) {
            cout << y << " ";
        }
        cout << endl;
    }

    return 0;
}