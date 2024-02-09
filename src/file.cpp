#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include "file.h"
using namespace std;

File::File(string fileName) {
    File::fileName = fileName;
}

string File::readFileName() {
    string fileName;
    do {
        cout << ">> Masukkan nama file: ";
        cin >> fileName;
        in.open("test/" + fileName);
        if (!in.is_open()) {
            cerr << "Error: Tidak ada file dengan nama test/" << fileName << "!" << endl;
        }
        cout << "\n";
    } while (!in.is_open()); 
    in.close();
    return "test/" + fileName;
}

Solver File::fromFile() {
    int buffsize, row, col, countSeq, reward;
    string token;
    in.open(fileName);
    in >> buffsize >> row >> col;
    Solver s(buffsize, row, col);

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            in >> token;
            s.setElmt(i, j, token);
        }  
    }

    in >> countSeq;
    in.ignore();
    for (int i = 0; i < countSeq; i++) {
        getline(in, token);
        in >> reward;
        s.addSequence(token);
        s.addReward(reward);
        in.ignore();
    }
    in.close();
    return s;
 }

 void File::save() {
 }