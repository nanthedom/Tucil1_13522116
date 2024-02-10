# Tugas Kecil 1 IF2211 Strategi Algoritma
Penyelesaian Cyberpunk 2077 Breach Protocol dengan Algoritma Brute Force

## Daftar Isi
- [Tugas Kecil 1 IF2211 Strategi Algoritma](#Tugas-Kecil-1-IF2211-Strategi-Algoritma)
  - [Daftar Isi](#Daftar-Isi)
  - [Ringkasan](#Ringkasan)
  - [Struktur Program](#Struktur-Program)
  - [Bahasa](#Bahasa)
  - [Cara Menjalankan](#Cara-Menjalankan)
  - [Author](#Author)

## Ringkasan
Cyberpunk 2077 Breach Protocol merupakan minigame yang berisi simulasi peretasan jaringan local dari ICE (Intrusion Countermeasures Electronics) pada permainan Cyberpunk 2077. Komponen permainan ini terdiri dari token alfanumerik, matrix dari token-token, sekuens beserta rewardnya, dan buffer untuk menyusun token. Permainan dimulai dengan pemain memilih satu token pada posisi baris paling atas dari matrix lalu bergerak dengan pola vertikal-horizontal secara bergantian dan tidak melebihi ukuran buffer.

Program ini akan memberikan solusi dari permainan Breach Protocol yang paling optimal untuk setiap kombinasi matrix, sekuens, dan ukuran buffer dengan menggunakan algoritma brute force. Solusi yang diperoleh merupakan hasil dari langkah untuk mendapatkan reward maksimal dengan menggunakan buffer seminimal mungkin, yang ditampilkan dengan perolehan reward, token, dan urutan koordinatnya.

## Struktur Program
```bash
.
│   
├───bin                          # Executable
│    │  main.exe
│
├───doc                          # Documentation
│    │  Tucil1_13522116
│
├───src                          # Source code
│    │  file.cpp
│    │  file.h
│    │  main.cpp
│    │  solver.cpp
│    │  solver.h
│
├───test                        
│    ├─── input
│    │      │ # all input from file .txt
│    │
│    ├─── output
│           │ # all output from testing
│
│ README.md
.
```

## Bahasa
* [C++](https://isocpp.org/)

## Cara Menjalankan
Program berbasis terminal menggunakan bahasa C++, pastikan perangkat yang Anda gunakan memiliki g++.
1. Clone Repository
   ```sh
   git clone https://github.com/nanthedom/Tucil1_13522116.git
   ```
2. Buka folder "Tucil1_13522116" di terminal, lalu run:
   ```sh
   ./bin/main.exe
   ```
3. Program telah berjalan dan pastikan input yang anda masukkan *valid* untuk kenyamanan penggunaan.

## Author
Naufal Adnan - 13522116@std.stei.itb.ac.id