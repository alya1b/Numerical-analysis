// ConsoleApplication11.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include<iostream>
#include "math.h"
#include <iomanip>
using namespace std;

template <class Value>
int Sign(Value Val) {
    if (Val == 0.)  return 0;
    if (Val > 0.)  return 1;
    else return -1;
}

int main()
{
    setlocale(LC_CTYPE, "ukr");
    const int n = 4;
    float A[n][n]; // матриця
    float S[n][n];
    float D[n][n];
    float b[n], x[n], y[n];

    //вводимо матрицю
    cout << "введiть елементи симетричної  матрицi" << endl;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            cin >> A[i][j];
        }

    //перевірка на симетричність
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            if (A[i][j] != A[j][i])
            {
                cout << "Матриця не симетрична" << endl;
            }
        }
    //вводимо вектор 
    cout << "введiть елементи вектора b" << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> b[i];
    }

    //заповнюємо D,S
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            S[i][j] = 0;
            D[i][j] = 0;
        }

    D[0][0] = Sign(A[0][0]);
    S[0][0] = sqrt(A[0][0]);

    S[0][1] = A[0][1] / (D[0][0] * S[0][0]);
    S[0][2] = A[0][2] / (D[0][0] * S[0][0]);
    S[0][3] = A[0][3] / (D[0][0] * S[0][0]);

    D[1][1] = Sign(A[1][1] - S[0][1] * S[0][1] * D[0][0]);
    S[1][1] = sqrt(abs(A[1][1] - S[0][1] * S[0][1] * D[0][0]));
    S[1][2] = (A[1][2] - S[0][1] * S[0][2] * D[0][0]) / (D[1][1] * S[1][1]);
    S[1][3] = (A[1][3] - S[0][1] * S[0][3] * D[0][0]) / (D[1][1] * S[1][1]);

    D[2][2] = Sign(A[2][2] - S[0][2] * S[0][2] * D[0][0] - S[1][2] * S[1][2] * D[1][1]);
    S[2][2] = sqrt(abs(A[2][2] - S[0][2] * S[0][2] * D[0][0] - S[1][2] * S[1][2] * D[1][1]));
    S[2][3] = (A[2][3] - S[0][2] * S[0][3] * D[0][0] - S[1][2] * S[1][3] * D[1][1]) / (D[2][2] * S[2][2]);

    D[3][3] = Sign(A[3][3] - S[0][3] * S[0][3] * D[0][0] - S[1][3] * S[1][3] * D[1][1] - S[2][3] * S[2][3] * D[2][2]);
    S[3][3] = sqrt(abs(A[3][3] - S[0][3] * S[0][3] * D[0][0] - S[1][3] * S[1][3] * D[1][1] - S[2][3] * S[2][3] * D[2][2]));

    //виводимо S,D
    cout << "S:" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << setw(10) << S[i][j] << " ";

        }
        cout << endl;
    }
    cout << "D:" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << setw(3) << D[i][j] << " ";

        }
        cout << endl;
    }
    //Знаходимо у 
    float ST[4][4];
    float STD[4][4];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            ST[i][j] = S[j][i];
        }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            if (D[j][j] == 1)
                STD[i][j] = ST[i][j];
            else STD[i][j] = (-1) * ST[i][j];
        }
    //STDy=b
    y[0] = b[0] / STD[0][0];
    y[1] = (b[1] - y[0] * STD[1][0]) / STD[1][1];
    y[2] = (b[2] - y[0] * STD[2][0] - y[1] * STD[2][1]) / STD[2][2];
    y[3] = (b[3] - y[0] * STD[3][0] - y[1] * STD[3][1] - y[2] * STD[3][2]) / STD[3][3];
    //Sx=y
    x[3] = y[3] / S[3][3];
    x[2] = (y[2] - S[2][3] * x[3]) / S[2][2];
    x[1] = (y[1] - S[1][2] * x[2] - S[1][3] * x[3]) / S[1][1];
    x[0] = (y[0] - S[0][1] * x[1] - S[0][2] * x[2] - S[0][3] * x[3]) / S[0][0];

    cout << "x[1] = " << x[0] << endl;
    cout << "x[2] = " << x[1] << endl;
    cout << "x[3] = " << x[2] << endl;
    cout << "x[4] = " << x[3] << endl;

    //визначник
    cout << "Визначник" << endl;
    float v = 1;
    for (int i = 0; i<4; i++)
    {
        v = v * S[i][i] * S[i][i] * D[i][i];
    }
    cout << v << endl;


    system("pause");
    return 0;
}

