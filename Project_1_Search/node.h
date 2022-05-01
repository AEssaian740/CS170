#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <cmath>

class Node {
private:
    vector<vector<int>> puzzle {
        {8, 6, 7},
        {2, 5, 4},
        {3, 0, 1}};                                     // Starting position of puzzle set to 31-move solution
    vector<vector<int>> winCondition{
        {1, 2, 3}, 
        {4, 5, 6}, 
        {7, 8, 0}};                                     // Win condition
    bool visited;
    double gCost = 0.0;                                 // Cost from initial state to current
    double hCost = 0.0;                                 // Hueristic cost
    double fCost = 0.0;                                 // Total cost of state
    Node *parent;                                       // Pointer to parent node
    int blank[2] = {2, 1};                              // Coord of blank tile
public:
    Node();
    Node(Node *n);
    ~Node();
    void upMove(priority_queue<Node> &frontier);        // Moves blank tile up if possible
    void downMove(priority_queue<Node> &frontier);      // Moves blank tile down if possible
    void leftMove(priority_queue<Node> &frontier);      // Moves blank tile left if possible
    void rightMove(priority_queue<Node> &frontier);     // Moves blank tile right if possible
    void setgCost(double g);
    void sethCost(double h);
    double getFCost();                                  // Outputs total cost of state
    bool bVisited();                                    // Checks if node has been visited
    bool checkWin();                                    // Checks if the node contains the win condition
    void sVisited();                                    // Sets node visited to true
    void setPuzzle(vector<vector<int>> p);              // Swaps default puzzle with user inputted puzzle
    void setBlank();                                    // Used for user-created puzzles to find the blank tile.
    void printPuzzle();
    Node UCSearch(priority_queue<Node> &frontier);
    Node aStarMT(priority_queue<Node> &frontier);
    Node aStarED(priority_queue<Node> &frontier);
};

#endif