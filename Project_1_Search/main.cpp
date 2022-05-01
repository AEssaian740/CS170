#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <cmath>
#include "node.h"

using namespace std;

// TODO
//*Build the 8-puzzle
//*Implement Uniform Cost Search
//*Implement A* with Misplaced Tile hueristic
//*Implement A* with Euclidean Distance hueristic

Node::Node() {
    visited = false;
    gCost = 0;
    hCost = 0;
    fCost = 0;
    parent = nullptr;
}

Node::Node(Node *n) {
    puzzle = n->puzzle;
    visited = false;
    gCost = n->gCost;
    hCost = n->hCost;
    fCost = n->fCost;
    parent = n;
}

int main() {
    int ans = 1;
    Node state = Node();
    priority_queue<Node> frontier;
    
    cout << "Welcome to 862072094 8 puzzle solver.\nType \"1\" to use a default "
            "puzzle, or \"2\" to enter your own puzzle.\n";
    cin >> ans;

    if (ans == 2) {
        vector<vector<int>> pTemp;
        cout << "Enter your puzzle, use a zero to represent the blank tile.\n";

        for (int i = 0; i < 3; i++) {
        vector<int> temp;
        cout << "Enter the numbers for row " << i + 1 << " separately:\n";
        for (int j = 0; j < 3; j++) {
            cin >> ans;
            temp.push_back(ans);
        }
        pTemp.push_back(temp);
        temp.clear();
        }
        state.setPuzzle(pTemp);
        state.setBlank();
        pTemp.clear();
    }

    /*
    cout << "Enter your choice of algorithm:\n"
        << "1. Uniform Cost Search\n"
        << "2. A* with the Misplaced Tile hueristic\n"
        << "3. A* with the Eucledian Distance hueristic\n";
    cin >> ans;

    switch (ans) {
    case 1:
        state.UCSearch(frontier);
        break;
    case 2:
        state.aStarMT(frontier);
        break;
    case 3:
        state.aStarED(frontier);
        break;
    }
    */
    state.printPuzzle();
}