// ConsoleApplication13.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

using namespace std;
float MaxVector(float a[4])
{
    float max = abs(a[0]);
    if (abs(a[1]) > max) max = abs(a[1]);
    if (abs(a[2]) > max) max = abs(a[2]);
    if (abs(a[3]) > max) max = abs(a[3]);
    return max;
}

int main()
{
    setlocale(LC_ALL, "ukr");
    // çì³íí³
    float A[4][4] = { {4,1,0,2} ,{1,3,0,0} ,{0,0,2,1} ,{2,0,1,4}, };
    float b[4] = {14,7,10,21};
    float x1[4];
    float x2[4];
    float eps=0.01;//òî÷í³ñòü
    float error[4];//òóò ïåðåâ³ðÿºìî òî÷í³ñòü

    for (int i = 0; i < 4; i++)
    {
        if (A[i][i] < A[i][0] + A[i][1] + A[i][2] + A[i][3] - A[i][i])
            cout << "Ìàòðèöÿ íåêîðåêòíà" << endl;
    }
    //ïî÷àòêîâå íàáëèæåííÿ õ0(0.0.0.0)
    for (int i = 0; i < 4; i++)
    {
        x1[i] = 0;
    }
    int iter = 1;//ê-ñòü ³òåðàö³é
    do {
        x2[0] = (-A[0][1] * x1[1] - A[0][2] * x1[2] - A[0][3] * x1[3]+b[0]) / A[0][0];
        x2[1] = (-A[1][0] * x2[0] - A[1][2] * x1[2] - A[1][3] * x1[3]+b[1]) / A[1][1];
        x2[2] = (-A[2][1] * x2[1] - A[2][0] * x2[0] - A[2][3] * x1[3]+b[2]) / A[2][2];
        x2[3] = (-A[3][1] * x2[1] - A[3][2] * x2[2] - A[3][0] * x2[0]+b[3]) / A[3][3];

        error[0] = abs(x1[0] - x2[0]);
        error[1] = abs(x1[1] - x2[1]);
        error[2] = abs(x1[2] - x2[2]);
        error[3] = abs(x1[3] - x2[3]);

        if (iter == 1) cout << "Норма векторів на ітерації 1: " << setprecision(10) << MaxVector(error) << endl;
        iter++;
        x1[0] = x2[0];
        x1[1] = x2[1];
        x1[2] = x2[2];
        x1[3] = x2[3];

        cout << "Iòåðàöiÿ " << iter << endl;
        cout << "x[1] = " << setprecision(10) << x1[0] << endl;
        cout << "x[2] = " << setprecision(10) << x1[1] << endl;
        cout << "x[3] = " << setprecision(10) << x1[2] << endl;
        cout << "x[4] = " << setprecision(10) << x1[3] << endl;
        
    
    } while (MaxVector(error) > eps);

    cout << "Норма векторів на останній ітерації: " << MaxVector(error) << endl;
    cout << "x[1] = " << setprecision(10) << x1[0]<<endl;
    cout << "x[2] = " << setprecision(10) << x1[1] << endl;
    cout << "x[3] = " << setprecision(10) << x1[2] << endl;
    cout << "x[4] = " << setprecision(10) << x1[3] << endl;
    //


    return 0;
}
