#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <cmath>
#include <utility>

using namespace std;

class Node {
private:
    vector<vector<int>> puzzle {
        {8, 6, 7},
        {2, 5, 4},
        {3, 0, 1}};                                             // Starting position of puzzle set to 31-move solution
    vector<vector<int>> winCondition{
        {1, 2, 3}, 
        {4, 5, 6}, 
        {7, 8, 0}};                                             // Win condition
    bool visited;
    double gCost;                                               // Cost from initial state to current
    double hCost;                                               // Hueristic cost
    double fCost;                                               // Total cost of state
    Node *parent;                                               // Pointer to parent node
    pair<int,int> blank;                                        // Coord of blank tile
public:
    Node();
    Node(Node *n);
    ~Node();
    void upMove(priority_queue<Node> &frontier);                // Moves blank tile up if possible
    void downMove(priority_queue<Node> &frontier);              // Moves blank tile down if possible
    void leftMove(priority_queue<Node> &frontier);              // Moves blank tile left if possible
    void rightMove(priority_queue<Node> &frontier);             // Moves blank tile right if possible
    void setGCost(double g) { gCost = g; }
    void setHCost(double h) { hCost = h; }
    double getGCost() { return gCost; }
    double getHCost() { return hCost; }
    double getFCost() { return gCost + hCost; }                 // Outputs total cost of state
    bool bVisited();                                            // Checks if node has been visited
    bool checkWin();                                            // Checks if the node contains the win condition
    void sVisited();                                            // Sets node visited to true
    void setPuzzle(vector<vector<int>> p) { puzzle = p; }       // Swaps default puzzle with user inputted puzzle
    void setBlank();                                            // Used for user-created puzzles to find the blank tile.
    int printBlank() {cout<<blank.first<<blank.second;}
    void printPuzzle();
    Node UCSearch(priority_queue<Node> &frontier);
    Node aStarMT(priority_queue<Node> &frontier);
    Node aStarED(priority_queue<Node> &frontier);
    bool operator<(const Node& n) const { return fCost < n.fCost; }
};

#endif