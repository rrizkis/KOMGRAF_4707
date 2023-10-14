/*
RIZQY SAPUTRA
A11.2021.13783
KOMGRAF 4707
Homework 2 : Operasi Hitung Matriks
*/
#include <iostream>
using namespace std;

void inputMatriks(int** matriks, int m, int n) {
    cout << "Masukkan nilai matriks:" << endl;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << "Baris " << i + 1 << ", Kolom " << j + 1 << ": ";
            cin >> matriks[i][j];
        }
    }
}

void tambahMatriks(int** A, int** B, int** hasil, int m, int n){
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            hasil[i][j] = A[i][j] + B[i][j];
        }
    }
}

void kurangMatriks(int** A, int** B, int** hasil, int m, int n){
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            hasil[i][j] = A[i][j] - B[i][j];
        }
    }
}

void kaliSkalar(int** matriks, int skalar, int** hasil, int m, int n){
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            hasil[i][j] = matriks[i][j] * skalar;
        }
    }
}

void kaliMatriks(int** A, int** B, int** hasil, int m, int n, int p){
    for (int i = 0; i < m; i++){
        for (int j = 0; j < p; j++){
            hasil[i][j] = 0;
            for (int k = 0; k < n; k++){
                hasil[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    int m, n, p; 
    cout << "Halo, selamat datang di Kalkulator Matriks :)" << endl;
    cout << "Tentukan ukuran matriks yang akan kamu hitung!" << endl;
    cout << "Masukkan jumlah baris matriks A: ";
    cin >> m;
    cout << "Masukkan jumlah kolom matriks A: ";
    cin >> n;
    cout << "Masukkan jumlah kolom matriks B (jumlah baris matriks B harus sama dengan kolom matriks A): ";
    cin >> p;

    int** matriksA = new int*[m];
    for (int i = 0; i < m; i++) {
        matriksA[i] = new int[n];
    }

    int** matriksB = new int*[n];
    for (int i = 0; i < n; i++) {
        matriksB[i] = new int[p];
    }

    int** hasil = new int*[m];
    for (int i = 0; i < m; i++) {
        hasil[i] = new int[p];
    }

    cout << "Masukkan angka untuk matriks A:" << endl;
    inputMatriks(matriksA, m, n);
    cout << "Masukkan angka untuk matriks B:" << endl;
    inputMatriks(matriksB, n, p);

    cout << "\n========================"<< endl;
    cout << "Matriks A : " << endl;
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            cout << matriksA[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    cout << "Matriks B : " << endl;
    for(int i=0; i<n; i++){
        for(int j=0; j<p; j++){
            cout << matriksB[i][j] << " ";
        }
        cout << endl;
    }

    int pilihan;
    do {
        cout << "\n========================"<< endl;
        cout << "\nMenu Operasi Matriks:" << endl;
        cout << "1. Penjumlahan Matriks" << endl;
        cout << "2. Pengurangan Matriks" << endl;
        cout << "3. Perkalian Matriks" << endl;
        cout << "4. Perkalian Skalar" << endl;
        cout << "5. Keluar" << endl;
        cout << "\nPilih operasi (1-5): ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambahMatriks(matriksA, matriksB, hasil, m, n);
                cout << "\nHasil Penjumlahan Matriks A dan B: \n" << endl;
                break;
            case 2:
                kurangMatriks(matriksA, matriksB, hasil, m, n);
                cout << "\nHasil Pengurangan Matriks A dan B: \n" << endl;
                break;
            case 3:
                kaliMatriks(matriksA, matriksB, hasil, m, n, p);
                cout << "\nHasil Perkalian Matriks A dan B: \n" << endl;
                break;
            case 4:
                int skalar;
                cout << "Masukkan skalar: ";
                cin >> skalar;

                char matriksPilihan;
                cout << "Pilih matriks yang akan dikalikan skalar (A/B): ";
                cin >> matriksPilihan;

                if (matriksPilihan == 'A' || matriksPilihan == 'a') {
                    kaliSkalar(matriksA, skalar, hasil, m, n);
                    cout << "\nHasil Perkalian Skalar Matriks A dengan " << skalar << ":\n" << endl;
                } else if (matriksPilihan == 'B' || matriksPilihan == 'b') {
                    kaliSkalar(matriksB, skalar, hasil, n, p);
                    cout << "\nHasil Perkalian Skalar Matriks B dengan " << skalar << ":\n" << endl;
                } else {
                    cout << "\nPilihan matriks tidak valid." << endl;
                }
                break;
            case 5:
                cout << "\nTerima kasih telah menggunakan Kalkulator Matriks :)" << endl;
                break;
            default:
                cout << "\nInput tidak valid :(" << endl;
                break;
        }

        if (pilihan != 5) {
            for (int i = 0; i < m; i++){
                for (int j = 0; j < p; j++){
                    cout << hasil[i][j] << " ";
                }
                cout << endl;
            }
        }
    } while (pilihan != 5);

    for (int i = 0; i < m; i++){
        delete[] matriksA[i];
    }
    delete[] matriksA;

    for (int i = 0; i < n; i++){
        delete[] matriksB[i];
    }
    delete[] matriksB;

    for (int i = 0; i < m; i++){
        delete[] hasil[i];
    }
    delete[] hasil;

    return 0;
}

