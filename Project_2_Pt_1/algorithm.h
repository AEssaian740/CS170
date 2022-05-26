#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <cmath>
#include <utility>
#include <algorithm>
#include <cstdlib> 
#include <ctime> 
#include <iomanip>

using namespace std;

class Algorithm {
private:
int numFeat;
int numAlgo;
double curRand;
vector<int> features;
public:
Algorithm();
Algorithm(int nFeat, int nAlgo);
~Algorithm();
double fowardSearch();
double backElimSearch();
double stubRand();
};

#endif