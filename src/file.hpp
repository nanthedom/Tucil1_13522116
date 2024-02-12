#ifndef __FILE_H
#define __FILE_H

#include <iostream>
#include <string>
#include <fstream>
#include "solver.hpp"
using namespace std;

class File {

    public:
        ifstream in;
        ofstream out;
        string fileName;

        // konstruktor
        File(string fileName);
        
        // load & save
        string readFileName();
        Solver fromFile();
        void saveToFile(Solver solve, int duration);
};

#endif