// ConsoleApplication14.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
using namespace std;

void inversion(double A[4][4], int N)
{
    double temp;
    double E[4][4];
    N = 4;

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            E[i][j] = 0.0;

            if (i == j)
                E[i][j] = 1.0;
        }

    for (int k = 0; k < N; k++)
    {
        temp = A[k][k];

        for (int j = 0; j < N; j++)
        {
            A[k][j] /= temp;
            E[k][j] /= temp;
        }

        for (int i = k + 1; i < N; i++)
        {
            temp = A[i][k];

            for (int j = 0; j < N; j++)
            {
                A[i][j] -= A[k][j] * temp;
                E[i][j] -= E[k][j] * temp;
            }
        }
    }

    for (int k = N - 1; k > 0; k--)
    {
        for (int i = k - 1; i >= 0; i--)
        {
            temp = A[i][k];

            for (int j = 0; j < N; j++)
            {
                A[i][j] -= A[k][j] * temp;
                E[i][j] -= E[k][j] * temp;
            }
        }
    }

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            A[i][j] = E[i][j];

}

double MaxVector(double a[4])
{
    float max = abs(a[0]);
    if (abs(a[1]) > max) max = abs(a[1]);
    if (abs(a[2]) > max) max = abs(a[2]);
    if (abs(a[3]) > max) max = abs(a[3]);
    return max;
}
double matnorm(double a[4][4])
{
    double r[4] = {0,0,0,0};
    for(int i=0; i<4; i++)
        for (int j = 0; j < 4; j++)
        {
            r[i] += abs(a[i][j]);
        }
    return MaxVector(r);
}

int main()
{
    setlocale(LC_ALL,"ukr");

    double A[4][4]= { {4,1,0,2} ,{1,3,0,0} ,{0,0,2,1} ,{2,0,1,4}, };
    double m1 = matnorm(A);
    cout << "Норма початкової матрицi: "<< m1 << endl;
    inversion(A, 4);
    cout << "Обернена матриця:" << endl;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
            cout << A[i][j] << "  ";

        cout << std::endl;
    }
    double m2 = matnorm(A);
    cout << "Норма оберненої матрицi: " << m2 << endl;
    cout << "Число обумовленостi:" << endl;
    cout << m1 * m2 << endl;



    system("pause");
    return 0;
}
