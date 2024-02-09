#ifndef __FILE_H
#define __FILE_H

#include <fstream>
#include <string>
#include "solver.h"
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
        void save();
};

#endif