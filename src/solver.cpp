#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include "solver.h"
using namespace std;

Solver::Solver(int buffsize, int row, int col) {
    point = 0;
    buffer = buffsize;
    matrix = vector<vector<string>>(row, vector<string>(col));
}

void Solver::setElmt(int x, int y, string val) {
    matrix[x][y] = val;
}

string Solver::getElmt(int x, int y) {
    return matrix[x][y];
}

int Solver::getRowLength() {
    return matrix.size();
}

int Solver::getColLength() {
    return matrix[0].size();
}

void Solver::displayMatrix() {
    for (int i = 0; i < getRowLength(); i++) {
        for (int j = 0; j < getColLength(); j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

void Solver::addReward(int val) {
    reward.push_back(val);
}

void Solver::addSequence(string val) {
    sequence.push_back(val);
}

void Solver::displayCoordinate() {
    for (int i = 0; i < coordinate.size(); i++) {
        int x = get<0>(coordinate[i]);
        int y = get<1>(coordinate[i]);
        cout << "(" << y + 1 << ", " << x + 1 << ")" << endl;
    }
}

int Solver::countReward(string val) {
    int res = 0;
    for (int i = 0; i < sequence.size(); i++) {
        sequence[i].erase(remove_if(sequence[i].begin(), sequence[i].end(), ::isspace), sequence[i].end());
        if (val.find(sequence[i]) != string::npos) {
            res += reward[i];
        }
    }
    return res;    
}

void Solver::search(int row, int col, string currToken, vector<vector<bool>> flag, bool vertikal, vector<tuple<int, int>> currCoord, int step) {
    tuple<int, int> p = make_tuple(row, col);
    currCoord.push_back(p);
    flag[row][col] = true;

    int currReward = countReward(currToken);
    if (currReward > point) {
        point = currReward;
        coordinate = currCoord;
    }

    if (step < buffer) {
        if (vertikal) {
            for (int i = 0; i < getRowLength(); i++) {
                if (!flag[i][col]) {
                    string newToken = currToken + getElmt(i, col);
                    search(i, col, newToken, flag, !vertikal, currCoord, step + 1);
                }
            }
        }
        else {
            for (int i = 0; i < getColLength(); i++) {
                if (!flag[row][i]) {
                    string newToken = currToken + getElmt(row, i);
                    search(row, i, newToken, flag, !vertikal, currCoord, step + 1);
                }
            }     
        }
    }

    currCoord.pop_back();
    flag[row][col] = false;
    return;
}

void Solver::solve() {
    vector<vector<bool>> flag(getRowLength(), vector<bool>(getColLength(), false));
    vector<tuple<int, int>> currCoord;
    for (int i = 0; i < getColLength(); i++) {
        search(0, i, getElmt(0, i), flag, true, currCoord, 1);
    }  
}