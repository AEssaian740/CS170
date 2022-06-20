#include "node.h"

using namespace std;

// TODO
//*[DONE]Build the 8-puzzle
//*[TEST]Implement Uniform Cost Search
//*Implement A* with Misplaced Tile hueristic
//*Implement A* with Euclidean Distance hueristic
void test(Node &laserJet);

Node::Node() {
    gCost = 1;
    hCost = 0;
    fCost = 0;
    qSize = 0;
    nExpanded = 0;
    parent = nullptr;
    setBlank();
}

Node::Node(Node *n) {
    puzzle = n->puzzle;
    gCost = n->gCost + 1;
    hCost = n->hCost;
    fCost = gCost + hCost;
    qSize = n->qSize;
    nExpanded = n->nExpanded;
    parent = n;
    blank.first = n->blank.first;
    blank.second = n->blank.second;
}

Node::~Node() {}

bool Node::checkVisited(Node n, vector<Node> visited) {
  for(int i = 0; i < visited.size(); i++) {
    n.printPuzzle();
    cout<<endl;
    visited.at(i).printPuzzle();
    cout<<endl;
    if(n.puzzle == visited.at(i).puzzle) {
      return true;
    } else {
      visited.push_back(n);
    }
  }
  return false;
}

void Node::upMove(priority_queue<Node> &frontier) {
    if(blank.first != 0) {
        Node child = Node(this);
        c1 = & child;
        swap(child.puzzle[blank.first][blank.second], 
            child.puzzle[blank.first - 1][blank.second]);
        child.blank.first -= 1;
        if(!checkVisited(child, visited)) {
          frontier.push(child);
        }
    }
}

void Node::downMove(priority_queue<Node> &frontier) {
    if(blank.first != 2) {
        Node child = Node(this);
        c2 = &child;
        swap(child.puzzle[blank.first][blank.second], 
            child.puzzle[blank.first + 1][blank.second]);
        child.blank.first += 1;
        if(!checkVisited(child, visited)) {
          frontier.push(child);
        }
    }
}

void Node::leftMove(priority_queue<Node> &frontier) {
    if(blank.second != 0) {
        Node child = Node(this);
        c3 = &child;
        swap(child.puzzle[blank.first][blank.second], 
            child.puzzle[blank.first][blank.second - 1]);
        child.blank.second -= 1;
        if(!checkVisited(child, visited)) {
          frontier.push(child);
        }
    }
}

void Node::rightMove(priority_queue<Node> &frontier) {
    if(blank.second != 2) {
        Node child = Node(this);
        c4 = &child;
        swap(child.puzzle[blank.first][blank.second], 
            child.puzzle[blank.first][blank.second + 1]);
        child.blank.second += 1;
        if(!checkVisited(child, visited)) {
          frontier.push(child);
        }
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

void Node::setHCost(int algo) {
  switch(algo) {
    case 1:
    hCost = 0;
    break;
    case 2:
    hCost = MTHuer();
    break;
    case 3:
    hCost = EDHuer();
    break;
  }  
}

int Node::MTHuer() {
  int mt = 0;

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if(puzzle[i][j] != winCondition[i][j])
        mt++;
    }
  }

  return mt;
}


int Node::EDHuer() {
  int ed = 0;
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			if(puzzle[i][j] != winCondition[i][j]){
				int n= 0;
				int m= 0;

				for(int y = 0; y < 3; y++){
					for(int z = 0; z < 3; z++){
						if(winCondition[y][z] == puzzle[i][j]){
							n = y;
							m = z;
						}
					}
				}
				n = pow(n-i,2);
				m = pow(m-j,2);
				ed += sqrt(n+m);
			}
		}
	}
	return ed;
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

Node Node::algorithm(priority_queue<Node> &frontier, int h) {
  Node temp;
  Node s;
  Node newMove;
  visited.clear();
  s=frontier.top();
  s.printPuzzle();
  cout <<endl<<endl;

  while (!frontier.empty()) {
    temp = frontier.top();
    temp.nExpanded++;
    temp.setHCost(h);

    if(temp.qSize < frontier.size()) {
      temp.qSize = frontier.size();
    }  
    if(temp.checkWin()) {
      return temp;
    }

    temp.upMove(frontier);
    temp.downMove(frontier);
    temp.leftMove(frontier);
    temp.rightMove(frontier);

    if(temp.getGCost() != 1) {
      cout << "The best state to expand with g(n) = " << temp.getGCost() << " and h(n) = " << temp.getHCost() << " is...\n";
      temp.printPuzzle();
      cout << "Expanding this node...\n";
    }

    frontier.pop();
    visited.push_back(temp);

    if(temp.nExpanded == 9000) {
      cout << "Over 9000 nodes, exiting search...\n";
      break;
    }
  }

  return s;
}

int main() {
  int ans = 1;
  Node state = Node();
  priority_queue<Node> frontier;
  Node result;

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

  cout << "Enter your choice of algorithm:\n"
       << "1. Uniform Cost Search\n"
       << "2. A* with the Misplaced Tile hueristic\n"
       << "3. A* with the Eucledian Distance hueristic\n";
  cin >> ans;
  
  result = Node(state.algorithm(frontier, ans));

  cout << "Goal!!!\n";
  cout << "To solve this problem, the search algorithm expanded a total of " <<result.getNExp() << " nodes.\n";
  cout << "The maximum number of nodes in the queue at any one time: " <<result.getQSize() << ".\n";
  cout << "The depth of the goal node was " << result.getGCost() << ".\n";
}