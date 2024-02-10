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
        int maxpts;
        vector<int> reward;
        vector<string> sequence;
        vector<tuple<int, int>> coordinate;
        vector<tuple<int, int>> currCoord;
        vector<vector<string>> matrix;
        vector<vector<bool>> flag;

        // konstruktor
        Solver(int buffsize, int row, int col);

        // setter
        void setElmt(int x, int y, string val);

        // getter
        string getElmt(int x, int y);
        int getRowLength();
        int getColLength();
        
        // output
        void displayMatrixToken();
        void displayCoordinate();
        void displayBuffer();
        void displayRewardSequence();

        // operasi lainnya
        void addReward(int val);
        void addSequence(string val);
        int countReward(string val);
        void search(int row, int col, string currToken, bool vertikal, int step);
};

#endif