#include <iostream>
#include <ctime>
#include <cstdlib>
#include "file.h"
#include "solver.h"
using namespace std;

void clearScreen() {
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
};

void printHeader() {
    cout << R"(
   ___     _  _   _                        _ __                    _     
  / __|   | || | | |__     ___      _ _   |  _ \  _  _    _ _     | |__  
 | (__     \_, | |  _ \   / -_)    |  _|  | .__/ | +| |  |   \    | / /  
  \___|   _|__/  |_.__/   \___|   _|_|_   |_|__   \_,_|  |_||_|   |_\_\;  
_|-----|_|-----|_|-----|_|-----|_|-----|_|-----|_|-----|_|-----|_|-----| 
---0-0---`-0-0---`-0-0---`-0-0---`-0-0---`-0-0---`-0-0---`-0-0---`-0-0--

# ----------WELCOME TO AWKWK-SYSTEM----------- #                     
# -------Cyberpunk 2077 Breach Protocol------- #     
# Temukan solusi dan dapatkan reward maksimal! #                     
------------------------------------------------)" << "\n\n";
};

void printMenu() {
    cout << "Pilih metode masukan:\n1. File\n2. Keyboard & random\n3. Keluar" << endl;
};

void printChoice() {
    cout << ">> Masukkan pilihan: ";
};

void printErrorInput() {
    cout << "Error: Input tidak valid!\n";
}

int inputChoice(int start, int end) {
    int choice;
    do {
        printChoice(); cin >> choice;
        if (choice < start || choice > end) {
            printErrorInput();
        } cout << "\n";        
    } while (choice < start || choice > end);
    return choice;
}

void runGame(int choice, Solver solve) {
    File file("");
    cout << "--Matrix Token--" << endl;
    solve.displayMatrix(); cout << endl;
    cout << "Ukuran buffer: " << solve.buffer << " [ ";
    for (int i = 0; i < solve.buffer; i++) {
        cout << "_ ";
    } cout << "]\n" << endl;
    cout << "Jumlah sekuens: " << solve.sequence.size() << endl;
    for (int i = 0; i < solve.reward.size(); i++) {
        cout << i + 1 << ". Reward: " << solve.reward[i]<< " - sekuens: " << solve.sequence[i] << endl;
    }
    cout << "Apakah ingin melihat solusi?\n1. Ya\n2. Tidak" << endl;
    choice = inputChoice(1, 2);
    if (choice == 1) {
        solve.solve();
        cout << "---Solusi---\nReward: " << solve.point << "\nToken: ";
        for (int i = 0; i < solve.coordinate.size(); i++) {
            int x = get<0>(solve.coordinate[i]);
            int y = get<1>(solve.coordinate[i]);
            cout << solve.getElmt(x, y) << " ";
        } 
        cout << "\nKoordinat:\n"; solve.displayCoordinate();
    }
    cout << "Apakah ingin menyimpan solusi?\n1. Ya\n2. Tidak" << endl;
    choice = inputChoice(1, 2);
    if (choice == 1) {
        file.save();
    }
}

int main() {
    bool run = true;
    int choice, countToken, countSeq, sizeSeq, randnum, randreward, buffer, row, col;;
    string fileName, input;
    vector<string> token;
    File file("");
    Solver solve(0, 0, 0);
    while (run)
    {
        clearScreen();
        printHeader();
        printMenu();
        printChoice();
        cin >> choice;
        switch (choice)
        {
        case 1:
            clearScreen();
            printHeader();
            fileName = file.readFileName();
            file = File(fileName);
            solve = file.fromFile();
            runGame(choice, solve);
            break;

        case 2:
            clearScreen();
            printHeader();

            do {
                cout << "Masukkan jumlah token unik: "; cin >> countToken;
                if (countToken < 1) {
                    cout << "Error: Jumlah token tidak boleh kosong!"<< endl;
                }
            } while (countToken < 1);

            cout << endl << "Masukkan token unik" << endl;
            token.resize(countToken);
            for (int i = 0; i < countToken; i++) {
                do {
                    cout << "Token unik ke-" << i + 1 << ": "; cin >> input;
                    if (input.length() != 2) {
                        cout << "Error: Token harus terdiri dari 2 karakter alfanumerik!\n Silakan masukkan kembali." << endl;
                    }
                } while (input.length() != 2);
                token[i] = input;
            }  

            cout << "\nMasukkan ukuran buffer: "; cin >> buffer;
            cout << "Masukkan baris matriks: "; cin >> row;
            cout << "Masukkan kolom matriks: "; cin >> col;
            solve = Solver(buffer, row, col);
            srand(time(nullptr));
            for (int i = 0; i < solve.getRowLength(); i++) {
                for (int j = 0; j < solve.getColLength(); j++) {
                    int randomIndex = rand() % token.size();
                    solve.setElmt(i, j, token[randomIndex]);
                }
            }

            do {
                cout << "Masukkan jumlah sekuens: "; cin >> countSeq;
                if (countSeq < 1) {
                    cout << "Error: Jumlah sekuens tidak boleh kosong!"<< endl;
                }
            } while (countSeq < 1);

            do {
                cout << "Masukkan ukuran maksimal sekuens: "; cin >> sizeSeq; cout << endl;
                if (sizeSeq < 2) {
                    cout << "Error: Ukuran minimal sekuens adalah 2!"<< endl;
                }
            } while (sizeSeq < 2);

            for (int i = 0; i < countSeq; i++) {
                do {
                    randnum = rand() % sizeSeq;
                } while (randnum < 2);
                
                input = "";
                for (int j = 0; j < randnum; j++) {
                    int randomIndex = rand() % token.size();
                    input = input + " " + token[randomIndex];
                }
                solve.addSequence(input);
                randreward = rand() % 41 + 10;
                solve.addReward(randreward);
            }
            runGame(choice, solve);
            break;

        case 3:
            run = false;

        default:
            break;;
        }
    }
}