#include "algorithm.h"

using namespace std;

Algorithm::Algorithm() {
    curRand = 0.0;
}
Algorithm::Algorithm(int nFeat, int nAlgo) {
    numFeat = nFeat;
    numAlgo = nAlgo;
}
Algorithm::~Algorithm() {

}
double Algorithm::fowardSearch() {
    double t1, t2, curRand = stubRand();
    int bestFT = 0;
    cout << "Using no features and \"random\" evaluation, I get an accuracy of " << fixed << setprecision(1) << curRand << "%\n"
         << "Beginning search.\n";
    do {
        for(int i = 1; i < features.size()+1; i++) {
            t1 = stubRand();
            cout << "Using feature(s) {" << i << "} accuracy is " << fixed << setprecision(1) << t1 << "%\n";
            if(t1> curRand) {
                t2 = t1;
                bestFT = i;
                features.push_back(bestFT);
            }
        }

        curRand = t2;
        cout << "Feature set {" << bestFT << "} was best, accuracy is " << fixed << setprecision(1) << curRand << "%\n";
    } while (t2 >= curRand);

    return curRand;
}
/*
double Algorithm::backElimSearch() {

}
*/
double Algorithm::stubRand() {
    double accuracy = 100*((double)rand()/(double)RAND_MAX);
    return accuracy;
}

int main() {
    srand((unsigned)time(NULL));
    char numFeat, numAlg;

    cout << "Welcome to Arman Essaian's Feature Selection Algorithm.\n"
        << "Please enter total number of features: ";
    cin >> numFeat;
    cout << "Type the number of the algorithm you want to run.\n"
        << "- Forward Selection\n- Backward Elimination\n";
    cin >> numAlg;

    Algorithm algo = Algorithm(numFeat - '0', numAlg - '0');

    switch(numAlg) {
        case '1':
        algo.fowardSearch();
        break;
        case '2':
        //algo.backElimSearch();
        break;
    }

}