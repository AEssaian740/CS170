#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <cmath>
#include <utility>
#include <algorithm>

using namespace std;

class Node {
private:
    vector<vector<int>> puzzle {
        {0, 1, 2},
        {4, 5, 3},
        {7, 8, 6}};                                             // Default Puzzle Level: Doable
    vector<vector<int>> winCondition{
        {1, 2, 3}, 
        {4, 5, 6}, 
        {7, 8, 0}};                                             // Win condition
    vector<Node> visited;
    int gCost;                                                  // Cost from initial state to current
    int hCost;                                                  // Hueristic cost
    int fCost;                                                  // Total cost of state
    long unsigned int qSize;
    int nExpanded;
    Node *parent;                                               // Pointer to parent node
    Node *c1;                                                   // Pointer to child node
    Node *c2;                                                   // Pointer to child node
    Node *c3;                                                   // Pointer to child node
    Node *c4;                                                   // Pointer to child node
    pair<int,int> blank;                                        // Coord of blank tile
public:
    Node();
    Node(Node *n);
    ~Node();
    void upMove(priority_queue<Node> &frontier);                // Moves blank tile up if possible
    void downMove(priority_queue<Node> &frontier);              // Moves blank tile down if possible
    void leftMove(priority_queue<Node> &frontier);              // Moves blank tile left if possible
    void rightMove(priority_queue<Node> &frontier);             // Moves blank tile right if possible
    void setHCost(int algo);
    int MTHuer();                                               // Calculates # of misplaced tiles
    int EDHuer();                                               // Calculates the Euclidian Distance
    int getGCost() { return gCost; }
    int getHCost() {return hCost;}
    int getFCost() { return gCost + hCost; }                    // Outputs total cost of state
    int getNExp() { return nExpanded; }
    int getQSize() { return qSize; }
    Node* getParent() { return parent; }
    vector<vector<int>> getPuzzle() { return puzzle; }
    bool checkWin();                                            // Checks if the node contains the win condition
    bool checkVisited(Node n, vector<Node> visited);
    void setPuzzle(vector<vector<int>> p) { puzzle = p; }       // Swaps default puzzle with user inputted puzzle
    void setBlank();                                            // Used for user-created puzzles to find the blank tile.
    void printBlank() {cout<<blank.first<<blank.second;}
    void printPuzzle();
    Node algorithm(priority_queue<Node> &frontier, int h);
    bool operator<(const Node& n) const { return fCost > n.fCost; }
};

#endif