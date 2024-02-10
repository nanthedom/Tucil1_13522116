#include <iostream>
#include <chrono>
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

void displayHeader() {
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

void displayMenu() {
    cout << "Pilih metode masukan:\n1. File\n2. Keyboard & random\n3. Keluar" << endl;
};

int inputChoice(int start, int end) {
    int choice;
    do {
        cout << ">> Masukkan pilihan: "; cin >> choice;
        if (choice < start || choice > end) {
            cout << "Error: Input tidak valid!\n";
        } cout << "\n";        
    } while (choice < start || choice > end);
    return choice;
}

void runGame(int choice, Solver solve) {
    File file("");
    solve.displayMatrixToken();
    solve.displayBuffer();
    solve.displayRewardSequence();
    solve.maxReward();

    cout << "\nApakah ingin melihat solusi?\n1. Ya\n2. Tidak" << endl;
    choice = inputChoice(1, 2);
    if (choice == 1) {    
        // brute force
        auto start = std::chrono::steady_clock::now();
        for (int i = 0; i < solve.getColLength(); i++) {
            solve.search(0, i, solve.getElmt(0, i), true, 1);
        }
        auto end = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        // output solusi
        cout << "---Solusi---\nReward: " << solve.point << "\nToken: ";
        for (int i = 0; i < solve.coordinate.size(); i++) {
            int x = get<0>(solve.coordinate[i]);
            int y = get<1>(solve.coordinate[i]);
            cout << solve.getElmt(x, y) << " ";
        }
        solve.displayCoordinate();
        if (solve.point == 0) {
            cout << "Tidak ada solusi optimal!\n" << endl;
        }
        cout << duration.count() << " ms" << endl;
        // save
        cout << "\nApakah ingin menyimpan solusi?\n1. Ya\n2. Tidak" << endl;
        choice = inputChoice(1, 2);
        if (choice == 1) {
            file.saveToFile(solve, duration.count());
        }
    }
    cout << "\nPress enter to continue...";
    cin.ignore();
    cin.get();
}

int main() {
    bool run = true;
    int choice, countToken, countSeq, sizeSeq, randnum, randreward, buffer, row, col;
    string fileName, input;
    vector<string> token;
    File file("");
    Solver solve(0, 0, 0);
    while (run)
    {
        clearScreen();
        displayHeader();
        displayMenu();
        choice = inputChoice(1, 3);
        switch (choice)
        {
        case 1:
            clearScreen();
            displayHeader();
            fileName = file.readFileName();
            file = File(fileName);
            solve = file.fromFile();
            runGame(choice, solve);
            break;

        case 2:
            clearScreen();
            displayHeader();

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