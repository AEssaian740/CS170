#include "node.h"

using namespace std;

// TODO
//*Build the 8-puzzle
//*Implement Uniform Cost Search
//*Implement A* with Misplaced Tile hueristic
//*Implement A* with Euclidean Distance hueristic

Node::Node() {
    visited = false;
    gCost = 1.0;
    hCost = 0.0;
    fCost = 0.0;
    parent = nullptr;
    blank.first = 2;
    blank.second = 1;
}

Node::Node(Node *n) {
    puzzle = n->puzzle;
    visited = false;
    gCost = n->gCost;
    hCost = n->hCost;
    fCost = n->fCost;
    parent = n;
    blank.first = n->blank.first;
    blank.second = n->blank.second;
}

Node::~Node() {}

void Node::upMove(priority_queue<Node> &frontier) {
    if(blank.first != 0) {
        Node child = Node(this);
        int temp = child.getGCost();
        temp++;
        child.setGCost(temp);
        swap(child.puzzle[blank.first][blank.second], 
            child.puzzle[blank.first - 1][blank.second]);
        child.blank.first -= 1;
        frontier.pop();
        frontier.push(child);
    }
}

void Node::downMove(priority_queue<Node> &frontier) {
    if(blank.first != 2) {
        Node child = Node(this);
        int temp = child.getGCost();
        temp++;
        child.setGCost(temp);
        swap(child.puzzle[blank.first][blank.second], 
            child.puzzle[blank.first + 1][blank.second]);
        child.blank.first += 1;
        frontier.pop();
        frontier.push(child);
    }
}

void Node::leftMove(priority_queue<Node> &frontier) {
    if(blank.second != 0) {
        Node child = Node(this);
        int temp = child.getGCost();
        temp++;
        child.setGCost(temp);
        swap(child.puzzle[blank.first][blank.second], 
            child.puzzle[blank.first][blank.second - 1]);
        child.blank.second -= 1;
        frontier.pop();
        frontier.push(child);
    }
}

void Node::rightMove(priority_queue<Node> &frontier) {
    if(blank.second != 0) {
        Node child = Node(this);
        int temp = child.getGCost();
        temp++;
        child.setGCost(temp);
        swap(child.puzzle[blank.first][blank.second], 
            child.puzzle[blank.first][blank.second + 1]);
        child.blank.second += 1;
        frontier.pop();
        frontier.push(child);
    }
}

void Node::setBlank() {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (puzzle[i][j] == 0) {
        blank.first = i;
        blank.second = j;
      }
    }
  }
}

void Node::printPuzzle() {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      cout << puzzle[i][j];
      cout << "  ";
    }
    cout << "\n";
  }
}

bool Node::checkWin() {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (puzzle[i][j] != winCondition[i][j]) {
        return false;
      }
    }
  }

  return true;
}

bool Node::bVisited() { return visited; }
void Node::sVisited() { visited = true; }


Node Node::UCSearch(priority_queue<Node> &frontier) {}
Node Node::aStarMT(priority_queue<Node> &frontier) {}
Node Node::aStarED(priority_queue<Node> &frontier) {}

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

    frontier.push(state);
    Node laserJet = frontier.top();

    while(true) {
      laserJet = frontier.top();
      laserJet.printBlank();
      cout<<"\n";
      laserJet.printPuzzle();
      cout<<"\n";

      cout<< "Choose direction:\n";
      cin>>ans;
      switch(ans) {
        case 1:
          laserJet.upMove(frontier);
        break;
        case 2:
          laserJet.downMove(frontier);
        break;
        case 3:
          laserJet.leftMove(frontier);
        break;
        case 4:
          laserJet.rightMove(frontier);
        break;
      }
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
}