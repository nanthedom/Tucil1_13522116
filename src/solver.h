#ifndef __SOLVER_H
#define __SOLVER_H

#include <string>
#include <vector>
#include <tuple>
using namespace std;

class Solver {
    public:
        int point;
        int buffer;  
        vector<int> reward;
        vector<string> sequence;
        vector<tuple<int, int>> coordinate;
        vector<vector<string>> matrix;

        // konstruktor
        Solver(int buffsize, int row, int col);

        // setter
        void setElmt(int x, int y, string val);

        // getter
        string getElmt(int x, int y);
        int getRowLength();
        int getColLength();
        
        // output
        void displayMatrix();
        void displayCoordinate();

        // operasi
        void addReward(int val);
        void addSequence(string val);
        int countReward(string val);
        void search(int row, int col, string currToken, vector<vector<bool>> flag, bool vertikal, vector<tuple<int, int>> currCoord, int step);
        void solve();
};

#endif