#include "solver.hpp"
using namespace std;

Solver::Solver(int buffsize, int row, int col) {
    point = 0;
    buffer = buffsize;
    matrix = vector<vector<string>>(row, vector<string>(col));
    flag = vector<vector<bool>>(row, vector<bool>(col, false));
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

void Solver::displayMatrixToken() {
    cout << "--Matrix Token--" << endl;
    for (int i = 0; i < getRowLength(); i++) {
        for (int j = 0; j < getColLength(); j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    } cout << endl;
}

void Solver::displayCoordinate() {
    cout << "\nKoordinat:\n";
    for (int i = 0; i < coordinate.size(); i++) {
        int x = get<0>(coordinate[i]);
        int y = get<1>(coordinate[i]);
        cout << y + 1 << ", " << x + 1 << endl;
    } cout << endl;
}

void Solver::displayBuffer() {
    cout << "Ukuran buffer: " << buffer << " [ ";
    for (int i = 0; i < buffer; i++) {
        cout << "_ ";
    } cout << "]\n" << endl;
}

void Solver::displayRewardSequence() {
    cout << "Jumlah sekuens: " << sequence.size() << endl;
    for (int i = 0; i < reward.size(); i++) {
        cout << i + 1 << ". Reward: " << reward[i]<< " - sekuens: " << sequence[i] << endl;
        sequence[i].erase(remove_if(sequence[i].begin(), sequence[i].end(), ::isspace), sequence[i].end());
    }
}

void Solver::addReward(int val) {
    reward.push_back(val);
}

void Solver::addSequence(string val) {
    sequence.push_back(val);
}

int Solver::countReward(string val) {
    int res = 0;
    for (int i = 0; i < sequence.size(); i++) {
        if (val.find(sequence[i]) != string::npos) {
            res += reward[i];
        }
    }
    return res;    
}

void Solver::search(int row, int col, string currToken, bool vertikal, int step) {
    tuple<int, int> p = make_tuple(row, col);
    currCoord.push_back(p);
    flag[row][col] = true;

    int currReward = countReward(currToken);
    if (currReward > point || (currReward == point && currCoord.size() < coordinate.size())) {
        point = currReward;
        coordinate = currCoord;
    }

    if (step < buffer) {
        if (vertikal) {
            for (int i = 0; i < getRowLength(); i++) {
                if (!flag[i][col]) {
                    search(i, col, currToken + getElmt(i, col), !vertikal, step + 1);
                }
            }
        }
        else {
            for (int i = 0; i < getColLength(); i++) {
                if (!flag[row][i]) {
                    search(row, i, currToken + getElmt(row, i), !vertikal, step + 1);
                }
            }     
        }
    }

    currCoord.pop_back();
    flag[row][col] = false;
}