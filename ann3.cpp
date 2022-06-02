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

float function(float x) {
    float y = x * x * x - 3 * x * x - 14 * x - 8 + sin(x);
    return y;
}

float XLagrange(float x, int number, float x_array[], float y_array[]) {

    float result = 0;
    for (int i = 0; i < number; ++i) {

        float l = 1;
        for (int j = 0; j < number; ++j)
            if (j != i)
                l *= (x - x_array[j]) / (x_array[i] - x_array[j]);
        result += y_array[i] * l;
    }

    return result;
}

float YLagrange(float y, int number, float x_array[], float y_array[]) {

    float result = 0;
    for (int i = 0; i < number; ++i) {

        float l = 1;
        for (int j = 0; j < number; ++j)
            if (j != i)
                l *= (y - y_array[j]) / (y_array[i] - y_array[j]);
        result += x_array[i] * l;
    }

    return result;
}



void SplCreator(float x[N + 1], float y[N + 1], float a1[N], float a2[N], float a3[N], float a4[N])
{
    float h[N];                        
    float b[N];                         
    float ftt[N + 1];                     

    for (int i = 0; i < N; i++)
    {
        h[i] = (x[i + 1] - x[i]);
        b[i] = (y[i + 1] - y[i]) / h[i];
    }

    ftt[0] = 0; 
    for (int i = 0; i < N - 1; i++)
        ftt[i + 1] = 3 * (b[i + 1] - b[i]) / (h[i + 1] + h[i]);
    ftt[N] = 0; 
    
    for (int i = 0; i < N; i++)
    {
        a1[i] = (ftt[i + 1] - ftt[i]) / (6 * h[i]);
        a2[i] = ftt[i] / 2;
        a3[i] = b[i] - h[i] * (ftt[i + 1] + 2 * ftt[i]) / 6;
        a4[i] = y[i];
    }
}


int main()
{   
    setlocale(LC_ALL,"ukr");
    float a = 5;
    float b = 6;
    float x_arr[10] = { 5.0 , 5.1 , 5.2 , 5.3 , 5.4 , 5.5 ,5.6 ,5.8 , 5.9 };
    float y_arr[10];
    for (int i = 0; i < 10; i++)
    {
        y_arr[i] = function(x_arr[i]);
    }

    cout << "Iнтерполяцiя" << endl;
    cout << "Iнтерполяцiйний полiном Лагранжа(прямий) має коефiцiенти:" << endl;
    for (int i = 0; i < 10; i++) {
        cout << XLagrange(y_arr[i], N, x_arr, y_arr) << "  ";
    }
    cout << endl;
    cout << "Iнтерполяцiйний полiном Лагранжа(обернений) має коефiцiенти:" << endl;
    for (int i = 0; i < 10; i++) {
        cout << YLagrange(x_arr[i], N, x_arr, y_arr) << "  ";
    }
   
    float a1[N], a2[N], a3[N], a4[N];
    SplCreator(x_arr, y_arr, a1, a2, a3, a4);
    cout << "Cплайни:" << endl;

    for (int i = 0; i < N; i++)
    { 

        cout << "Сплайн " << i + 1 << endl;
        cout << "a1 = " << setprecision(10) << a1[i] << "   a2 = " << setprecision(10) << a2[i] << "   a3 = " << setprecision(10) << a3[i] << "   a4 = " << setprecision(10)<< a4[i] << endl;
    }

    system("pause");
    return 0;
}