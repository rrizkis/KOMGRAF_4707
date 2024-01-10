#include <iostream>
#include <cmath>
#include <limits>

using namespace std;

double a[100][100];
double b[100];
double c[100];
double temp = 0;
double hasil;
int i, j;
double derajat;
double nilaiSin, nilaiCos, radian, epsilon;

void matrixTranslasi()
{
    for (i = 0; i < 3; i++)
    {
        c[i] = b[i] + a[2][i];
    }

    cout << "\nMatrix Koordinat Baru :" << endl;

    for (i = 0; i < 3; i++)
    {
        cout << c[i] << " ";
    }
    cout << endl;
}

void matrixRotasi()
{
    for (i = 0; i < 3; i++)
    {
        c[i] = a[0][i] * b[0] + a[1][i] * b[1];
    }

    cout << "\nMatrix Koordinat Baru :" << endl;

    for (i = 0; i < 3; i++)
    {
        cout << c[i] << " ";
    }
    cout << endl;
}

void matrixSkala()
{
    for (i = 0; i < 3; i++)
    {
        c[i] = a[i][i] * b[i];
    }

    cout << "\nMatrix Koordinat Baru :" << endl;

    for (i = 0; i < 3; i++)
    {
        cout << c[i] << " ";
    }
    cout << endl;
}

int main()
{
    int pilih;
    char akhir;
    do
    {
        cout << "Pilih operasi matriks berikut:\n1. Translasi\n2. Rotasi\n3. Skala" << endl;
        cin >> pilih;

        switch (pilih)
        {
        case 1:
            cout << "**********Matrix Translasi**********" << endl;
            cout << "Masukkan nilai matriks :" << endl;
            for (j = 0; j < 3; j++)
            {
                cout << "Baris Matrix " << j + 1 << " :" << endl;
                for (i = 0; i < 3; i++)
                {
                    cin >> a[i][j];
                }
            }
            cout << "\nMatrix Translasi:" << endl;

            for (j = 0; j < 3; j++)
            {
                for (i = 0; i < 3; i++)
                {
                    cout << a[i][j] << " ";
                }
                cout << endl;
            }
            cout << "Masukkan titik koordinat " << endl;

            for (j = 0; j < 3; j++)
            {
                cin >> b[j];
            }

            cout << "\nMatrix Koordinat :" << endl;

            for (j = 0; j < 3; j++)
            {
                cout << b[j] << " ";
                cout << endl;
            }

            matrixTranslasi();
            break;
        case 2:
            cout << "**********Matrix Rotasi**********" << endl;
            cout << "Masukkan nilai derajat : ";
            cin >> derajat;

            radian = derajat * M_PI / 180;
            nilaiSin = sin(radian);
            nilaiCos = cos(radian);
            epsilon = numeric_limits<double>::epsilon();
            if (fabs(nilaiCos) < epsilon)
            {
                nilaiCos = 0.0;
            }
            else if (fabs(nilaiSin) < epsilon)
            {
                nilaiSin = 0.0;
            }

            for (j = 0; j < 3; j++)
            {
                for (i = 0; i < 3; i++)
                {
                    if ((i == 0 && j == 0) || (i == 1 && j == 1))
                    {
                        a[i][j] = nilaiCos;
                    }
                    else if (i == 1 && j == 0)
                    {
                        a[i][j] = -nilaiSin;
                    }
                    else if (i == 0 && j == 1)
                    {
                        a[i][j] = nilaiSin;
                    }
                    else if ((i == 2 && j == 0) || (i == 2 && j == 1) || (i == 0 && j == 2) || (i == 1 && j == 2))
                    {
                        a[i][j] = 0;
                    }
                    else
                    {
                        a[i][j] = 1;
                    }
                }
            }
            cout << "\nMatrix Rotasi:" << endl;
            for (j = 0; j < 3; j++)
            {
                for (i = 0; i < 3; i++)
                {
                    cout << a[i][j] << " ";
                }
                cout << endl;
            }

            cout << "Masukkan titik koordinat " << endl;
            for (j = 0; j < 3; j++)
            {
                cin >> b[j];
            }

            cout << "\nMatrix Koordinat :" << endl;

            for (j = 0; j < 3; j++)
            {
                cout << b[j] << " ";
                cout << endl;
            }

            matrixRotasi();
            break;
        case 3:
            cout << "**********Matrix Skala**********" << endl;
            cout << "Masukkan nilai matriks :" << endl;
            for (j = 0; j < 3; j++)
            {
                cout << "Baris Matrix " << j + 1 << " :" << endl;
                for (i = 0; i < 3; i++)
                {
                    cin >> a[i][j];
                }
            }
            cout << "\nMatrix Skala :" << endl;

            for (j = 0; j < 3; j++)
            {
                for (i = 0; i < 3; i++)
                {
                    cout << a[i][j] << " ";
                }
                cout << endl;
            }

            cout << "Masukkan titik koordinat " << endl;

            for (j = 0; j < 3; j++)
            {
                cin >> b[j];
            }

            cout << "\nMatrix Koordinat :" << endl;

            for (j = 0; j < 3; j++)
            {
                cout << b[j] << " ";
                cout << endl;
            }

            matrixSkala();
            break;
        default:
            cout << "Pilihan Tidak Valid!!!" << endl;
            break;
        }
        cout << "Ulang lagi (Y/T) :" << endl;
        cin >> akhir;
    } while (akhir == 'Y' || akhir == 'y');

    return 0;
}

