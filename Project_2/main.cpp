#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>

using namespace std;

vector< vector<double> > data;
vector< vector<double> > features;

vector< vector<double > > adjustedData;

bool livesIn(int value, vector<int> v) {
    for(int i = 0; i < v.size(); i++) {
        if(value == v[i]) {
            return true;
        }
    }

    return false;
}

void cleanData(vector< vector< double > > data, vector<int> currSet, int featToAdd) {
    currSet.push_back(featToAdd);
    adjustedData = data;

    for(int i = 0; i < data.size(); i++) {
        for(int j = 0; j < data[i].size(); j++) {
            if(livesIn(j, currSet)) {} else {
                adjustedData[i][j] = 0;
            }
        }
    }

    return;
}

double getDistance(vector<double> objToClass, vector<double> kNeighbor) {
    double distance = 0;
    double x;

    for(int i = 1; i < objToClass.size(); i++) {
        x = pow(objToClass[i] - kNeighbor[i],2);
        distance += x;
    }

    return sqrt(distance);
}

double getAccuracy(vector< vector<double> > data, vector<int> currSet, int featToAdd) {
    cleanData(data, currSet, featToAdd);
    vector<double> objToClass;
    int objToClassLabel = 0;
    int nnLabel = 0;
    double numCorrClass = 0;

    for(int i = 0; i < data.size(); i++) {
        objToClass = adjustedData[i];
        objToClassLabel = data[i][0];
        double nnDist = 90000;
        double nnLocation = 90000;
        double distance = 0;

        for(int k = 0; k < data.size(); k++) {
            if(!(k == i)) {
                distance = getDistance(objToClass, adjustedData[k]);

                if(distance < nnDist) {
                    nnDist = distance;
                    nnLocation = k;
                    nnLabel = data[k][0];
                }
            }
        }

        if(objToClassLabel == nnLabel) {
            numCorrClass++;
        }
    }

    return (numCorrClass / data.size())*100;
}

int stubRand(vector< vector<double> > data, vector<int> currSet, int featToAdd) {
    return rand() % 100;
}

bool isInSet(int j, vector<int> currSet) {
    for(int i = 0; i < currSet.size(); i++) {
        if(currSet[i] == j) {
            return true;
        }
    }

    return false;
}

void fwdSelSearch(vector< vector<double> > data) {
    vector<int> currSet;
    vector<int> currSetTemp;
    double bestAcc = 0;
    vector<int> bestSet;
    double accuracy = 0;

    for(int i = 1; i < data[0].size(); i++) {
        int bestFeat;
        double currBestAcc = 0;

        for(int j = 1; j < data[0].size(); j++) {
            if(isInSet(j,currSet)) {} else {
                accuracy = getAccuracy(data, currSet, j);
                cout << "\tUsing features(s) {" << j <<"} accuracy is " << accuracy << "%\n";

                if(accuracy > currBestAcc) {
                    currBestAcc = accuracy;
                    bestFeat = j;

                    if(currBestAcc > bestAcc) {
                        currSetTemp = currSet;
                        currSetTemp.push_back(bestFeat);
                        bestSet = currSetTemp;
                        bestAcc = currBestAcc;
                    } else {
                        cout << "(Warning, Accuracy has decreased! Continuing search in case of local maxima)\n";
                    }
                }
            }
        }

        currSet.push_back(bestFeat);
        cout << "Feature set {" << bestFeat;
        for(int i = 0; i < bestSet.size(); i++) {
            if(bestFeat != bestSet[i]) {
                cout << "," << bestSet[i];
            }
        }
        cout << "} was best at an accuracy of " << currBestAcc << "%\n\n";
    }

    cout << "Search completed.\nThe best feature subset is {";
    for(int i = 0; i < bestSet.size(); i++) {
        cout << bestSet[i] << " ";
    }

    cout << "} with an accuracy of " << bestAcc << "%!\n";
    return;
}

double calcAccBackElim(vector< vector<double> > data, vector<int> currSet, int featToElim) {
    for(int k = 0; k < currSet.size(); k++) {
        if(currSet[k] == featToElim) {
            currSet.erase(currSet.begin()+k);
        }
    }

    adjustedData = data;
    for(int i = 0; i < data.size(); i++) {
        for(int j = 0; j < data[i].size(); j++) {
            if(livesIn(j, currSet)) {} else{
                adjustedData[i][j] = 0;
            }
        }
    }

    vector<double> objToClass;
    int objToClassLabel = 0;
    int nnLabel = 0;
    double numCorrClass = 0;

    for(int i = 0; i < data.size(); i++) {
        objToClass = adjustedData[i];
        objToClassLabel = data[i][0];
        double nnDist = 90000;
        double nnLocation = 90000;
        double distance = 0;

        for(int k = 0; k < data.size(); k++) {
            if(!(k == i)) {
                distance = getDistance(objToClass, adjustedData[k]);

                if(distance < nnDist) {
                    nnDist = distance;
                    nnLocation = k;
                    nnLabel = data[k][0];
                }
            }
        }

        if(objToClassLabel == nnLabel) {
            numCorrClass++;
        }
    }

    return (numCorrClass / data.size())*100;
}

void backElimSearch(vector< vector<double> > data) {
    vector<int> currSet;
    double accuracy = 0;
    vector<int> currSetTemp;
    double bestAcc = 0;
    vector<int> bestSet;
    
    for(int i = 1; i < data[0].size(); i++) {
        currSet.push_back(i);
    }
    for(int i = 1; i < data[0].size(); i++) {
        int currBestElimFeat;
        int currBestAcc = 0;

        for(int j = 1; j < data[0].size(); j++) {
            if(isInSet(j,currSet)) {
                accuracy = calcAccBackElim(data, currSet, j);
                cout << "\tUsing features(s) {" << j <<"} accuracy is " << accuracy << "%\n";

                if(accuracy > currBestAcc) {
                    currBestAcc = accuracy;
                    currBestElimFeat = j;

                    if(currBestAcc > bestAcc) {
                        bestAcc = currBestAcc;
                        bestSet = currSet;
                    } else {
                        cout << "(Warning, Accuracy has decreased! Continuing search in case of local maxima)\n";
                    }
                }
            }
        }
        for(int k = 0; k < currSet.size(); k++) {
            if(currSet[k] == currBestElimFeat) {
                currSet.erase(currSet.begin()+k);
            }
        }

        cout << "Feature set {" << currBestElimFeat;
        for(int i = 0; i < bestSet.size(); i++) {
            if(currBestElimFeat != bestSet[i]) {
                cout << "," << bestSet[i];
            }
        }
        cout << "} was best at an accuracy of " << currBestAcc << "%\n\n";
    }

    cout << "Search completed.\nThe best feature subset is {";

    for(int i = 0; i < bestSet.size(); i++) {
        cout << bestSet[i] << " ";
    }

    cout << "} with an accuracy of " << bestAcc << "%!\n";
    return;
}

int readFile(string filename) {
    string line;
    int numInstances=0;
    int numFeatures=0;
    double curr_data;
    ifstream myfile (filename);

    if(myfile.is_open()) {
        while(getline(myfile,line)) {
            numInstances++;
            istringstream ss(line);
            string word;
            double num;
            vector<double> instances;

            while( ss >> word) {
                num = atof(word.c_str());
                instances.push_back(num);
            }

            numFeatures = instances.size()-1;
            data.push_back(instances);
        }
    } else {
        cout << "Error opening file!\n";
        return -1;
    }

    cout << "This dataset has " << numFeatures << " features (not including the class attribute), and has " << numInstances << " instances\n";
    return 0;
}

int main() {
    srand (time(NULL));
    string filename;
    string f1 = "CS170_Spring_2022_Small_data__121.txt";
    string f2 = "CS170_Spring_2022_Large_data__121.txt";
    int algorithm = 1;

    cout << "Welcome to Arman Essaian's Feature Selection Algorithm Program!\n";

    cout << "Type in the name of the file to test: ";
    cin >> filename;

    //FOR TESTING ONLY::: default for testing
    //filename = f1;
    filename = f2;

    cout << "Type the number of the algorithm you want to run: ";
    cout << "\n\t (1) Forward selection \n\t (2) Backward Elimination\n";
    cin >> algorithm;

    cout << "\nProcessing data ... \n\t";

    if(readFile(filename) == -1) {
        cout << "Exiting\n";
        return -1;
    }

    if(algorithm == 1) {
        cout << "\nStarting forward selection...\n";
        fwdSelSearch(data);
    } else if(algorithm == 2) {
        cout << "\nStarting backward elimination...\n";
        backElimSearch(data);
    }
    cout << endl;
    return 0;
}
