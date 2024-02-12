#include "file.hpp"
using namespace std;

File::File(string fileName) {
    File::fileName = fileName;
}

string File::readFileName() {
    string fileName;
    do {
        cout << ">> Masukkan nama file: ";
        cin >> fileName;
        in.open("test/input/" + fileName);
        if (!in.is_open()) {
            cerr << "Error: Tidak ada file dengan nama test/input/" << fileName << "!" << endl;
        }
        cout << "\n";
    } while (!in.is_open()); 
    in.close();
    return "test/input/" + fileName;
}

Solver File::fromFile() {
    int buffsize, row, col, countSeq, reward;
    string token;
    in.open(fileName);
    in >> buffsize >> row >> col;
    Solver solve(buffsize, row, col);

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            in >> token;
            solve.setElmt(i, j, token);
        }  
    }

    in >> countSeq;
    in.ignore();
    for (int i = 0; i < countSeq; i++) {
        getline(in, token);
        in >> reward;
        solve.addSequence(token);
        solve.addReward(reward);
        in.ignore();
    }
    in.close();
    return solve;
 }

void File::saveToFile(Solver solve, int duration) {
    string input;
    cout << "Masukkan nama file: "; cin >> input;
    out.open("test/output/" + input);
    if (!out.is_open()) {
        cout << "Error: Gagal membuat file!" << endl;
        return;
    }

    out << solve.point << endl;
    for (int i = 0; i < solve.coordinate.size(); i++) {
        int x = get<0>(solve.coordinate[i]);
        int y = get<1>(solve.coordinate[i]);
        if (i == solve.coordinate.size() - 1) {
            out << solve.getElmt(x, y);
        }
        else {
            out << solve.getElmt(x, y) << " ";
        }
    }

    out << endl;
    for (int i = 0; i < solve.coordinate.size(); i++) {
        int x = get<0>(solve.coordinate[i]);
        int y = get<1>(solve.coordinate[i]);
        out << y + 1 << ", " << x + 1 << endl;
    }
    out << endl;
    out << duration << " ms";
    out.close();
    cout << "File berhasil disimpan di test/output/" << input << endl;
 }