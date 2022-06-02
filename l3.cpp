// l3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iomanip>
#include <math.h>
#include<vector>
#include<algorithm>
#include<cmath>
#define N 9

using namespace std;
const float pi = 3.1415926;

float f(float x) {
    float y = x * x + 5 * sin(x) - 1;
    return y;
}

void Cheb(float x[10], float a, float b)
{
    for (int i = 0; i < 10; i++)
    {
        x[i] = ((a + b) / 2) + ((b - a) / 2) * cos((2 * i + 3) * pi / (2 * 10));
    }
}

float Lagrange(float x, int n, float x_arr[], float y_arr[]) {

    float sum = 0;
    for (int i = 0; i < n; ++i) {

        float l = 1;
        for (int j = 0; j < n; ++j)
            if (j != i)
                l *= (x - x_arr[j]) / (x_arr[i] - x_arr[j]);
        sum += y_arr[i] * l;
    }

    return sum;
}

float Newton(float x, int n, float x_arr[], float y_arr[]) {

    double sum = y_arr[0];
    for (int i = 1; i < n; ++i) {

        float F = 0;
        for (int j = 0; j <= i; ++j) {

            float den = 1;
            for (int k = 0; k <= i; ++k)
                if (k != j)
                    den *= (x_arr[j] - x_arr[k]);

            F += y_arr[j] / den;
        }
        for (int k = 0; k < i; ++k)
            F *= (x - x_arr[k]);
        sum += F;
    }
    return sum;
}

void Spline(float x[N + 1], float y[N + 1], float A[N], float B[N], float C[N], float D[N])
{
    float h[N];                            // delta x
    float b[N];                            // delta y / delta x
    float ftt[N + 1];                      // f''(xi)

    // calc h & b
    for (int i = 0; i < N; i++)
    {
        h[i] = (x[i + 1] - x[i]);
        b[i] = (y[i + 1] - y[i]) / h[i];
    }

    // calc f''(xi)
    ftt[0] = 0; // f''(x0) = 0
    for (int i = 0; i < N - 1; i++)
        ftt[i + 1] = 3 * (b[i + 1] - b[i]) / (h[i + 1] + h[i]);
    ftt[N] = 0; // f''(xn) = 0

    // calc spline coefficients
    for (int i = 0; i < N; i++)
    {
        A[i] = (ftt[i + 1] - ftt[i]) / (6 * h[i]);
        B[i] = ftt[i] / 2;
        C[i] = b[i] - h[i] * (ftt[i + 1] + 2 * ftt[i]) / 6;
        D[i] = y[i];
    }
}

// receives points and Spline coefficients and print the functions
void PrintSpline(float x[N + 1], float A[N], float B[N], float C[N], float D[N])
{
    cout << " f(x) = d(x - xi)^3 + c(x - xi)^2 +d (x - xi) + a" << endl;
    cout << setw(12) << "  a  ";
    cout << setw(12) << "  b  ";
    cout << setw(12) << "  c  ";
    cout << setw(12) << "  d  ";
    cout << endl;
    for (int i = 0; i < N; i++)
    {
        cout << setw(12) << fixed << setprecision(5) <<A[i];
        cout << setw(12) << fixed << setprecision(5) << B[i]; 
        cout << setw(12) << fixed << setprecision(5) << C[i]; 
        cout << setw(12) << fixed << setprecision(5) << D[i];
        cout << endl;
    }
}

int main()
{
    float x_arr[10];
    float y_arr[10];

    float a = -3;
    float b = -2;

    Cheb(x_arr, a, b);

    for (int i = 0; i < 10; i++)
    {
        y_arr[i] = f(x_arr[i]);
    }

    cout << setw(5) << "x";
    cout << setw(15) << "f(x)   ";
    cout << setw(12) << "Lagrange(x)";
    cout << setw(12) << "Newton(x)";
    cout << endl;
    cout << "---------------------------------------" << endl;

    for (int i = 0; i < 10; i++) {

        cout << setw(3) << fixed << setprecision(8) << x_arr[i];
        cout << setw(12) << fixed << setprecision(6) << f(x_arr[i]);
        cout << setw(12) << fixed << setprecision(6) << Lagrange(x_arr[i], N, x_arr, y_arr);
        cout << setw(12) << fixed << setprecision(6) << Newton(x_arr[i], N, x_arr, y_arr);
        cout << endl;
    }
    cout << "==================================================" << endl;
    
    float A[N], B[N], C[N], D[N];
    Spline(x_arr, y_arr, A, B, C, D);
    PrintSpline(x_arr, A, B, C, D);
    
    system("pause");
    return 0;
}