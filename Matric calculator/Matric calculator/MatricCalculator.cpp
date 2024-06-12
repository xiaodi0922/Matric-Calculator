﻿#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;


ifstream matA("MatricesA.txt", ios::in);
ifstream matB("MatricesB.txt", ios::in);
ofstream history("log.txt", ios::out);
void option();
void closeAndSave(int, int);
void inc(int& x) {
    x++;
}


void addition(float[][20], float[][20], int, int);
void subtraction(float[][20], float[][20], int, int);
void multiplication(float[][20], float[][20], int, int, int, int);
void scalar(float[][20], int, int);
void min_max(float[][20], int, int);
void pandN(float[][20], int, int);
char opt;
float C[20][20]; //result
int h = 1; //Counter for log



//Function for inverse calculation
float determinant(float[][20], int);
void cofactor(float[][20], int);
void transpose(float[][20], float[][20], int);



int main() {
    cout << "Please do the calculation that involves 2 matrices first (+ or - or * AND NOT [inv or scalar or Min/Max)]" << endl;
    cout << "Thank you :)" << endl;
    int e = 1;
    while (e != 0) {
        float a[20][20], b[20][20];
        float d;
        int rA, rB, cA, cB;
        int x = 1;
        int r, c;
        char more;
        matA >> rA >> cA;
        matB >> rB >> cB;
        for (int i = 0; i < rA; ++i)
        {
            for (int j = 0; j < cA; ++j)
            {
                matA >> a[i][j];
            }
        }

        for (int i = 0; i < rB; ++i)
        {
            for (int j = 0; j < cB; ++j)
            {
                matB >> b[i][j];
            }
        }

        option();

        if (opt == '+') {
            if (rA != rB && cA != cB) {
                cout << "Please enter a valid row/column for (-) operation";
                return 0;
            }
            else {
                r = rA;
                c = cA;
                addition(a, b, r, c);
            }
        }
        else if (opt == '-') {
            if (rA != rB && cA != cB) {
                cout << "Please enter a valid row/column for (-) operation";
                return 0;
            }
            else {
                r = rA;
                c = cA;
                subtraction(a, b, r, c);
            }
        }
        else if (opt == '*')
        {
            if (cA != rB)
            {
                cout << "Please enter a valid row/column for (*) operation";
                return 0;
            }
            else
            {
                multiplication(a, b, rA, rB, cA, cB);
            }


        }
        else if (opt == 'S' || opt == 's') {
            r = rA;
            c = cA;
            scalar(a, r, c);
        }
        else if (opt == 'I' || opt == 'i') {
            r = rA;
            d = determinant(a, r);
            if (d == 0)
                cout << ("\nInverse of Entered Matrix is not possible\n");
            else
                cofactor(a, r);
        }
        else if (opt == 'M' || opt == 'm') {
            r = rA;
            c = cA;
            min_max(a, r, c);
        }
        else if (opt == 'E' || opt == 'e') {
            r = rA;
            c = cA;
            pandN(a, r, c);
        }

        cout << "\nDo you wish to do more calculation (Y|N) : ";
        cin >> more;
        switch (more) {
        case 'Y':
            cout << ("\nPlease make sure that the matrices needed to use is in the input file.\n\n");
            opt = 0;
            inc(h);

            break;
        case 'N':
            e = 0;
            history.close();
            matA.close();
            matB.close();

            break;
        }
    }
    return 0;

}

void option() //choose option for the calculation
{

    cout << "==========================" << endl;
    cout << "+: Sum of Matrix" << endl;
    cout << "-: Different of Matrix " << endl;
    cout << "*: Multiplication of Matrix" << endl;
    cout << "S or s: Scalar multiplication of Matrix" << endl;
    cout << "I or i: Inverse of Matrix" << endl;
    cout << "M or m: Maximum & Minimum of Matrix" << endl;
    cout << "E or e: Total of positive and negative numbers of Matrix" << endl;


    cout << "==========================" << endl;
    cout << "\nPlease choose your option: " << endl;
    cin >> opt;

}
void closeAndSave(int r, int c) {

    history << "\nResult: " << endl;
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {

            history << C[i][j] << "\t";
        }
        history << endl;
    }
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {

            C[i][j] = 0;
        }
    }
    history << endl;
}

void addition(float a[20][20], float b[20][20], int r, int c) {

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {

            C[i][j] = a[i][j] + b[i][j];
        }
        cout << endl;
    }
    cout << "The result of addition: " << endl;

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {

            cout << C[i][j] << "\t";
        }
        cout << endl;
    }
    history << h << endl;
    history << "\nMatricesA + Matrices B" << endl;
    history << "\nMatrices A : " << endl;
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {

            history << a[i][j] << "\t";
        }
        history << endl;
    }
    history << "\nMatrices B : " << endl;
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {

            history << b[i][j] << "\t";
        }
        history << endl;
    }
    closeAndSave(r, c);

}
void subtraction(float a[20][20], float b[20][20], int r, int c) {

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {

            C[i][j] = a[i][j] - b[i][j];
        }
        cout << endl;
    }
    cout << "The result of subtraction: " << endl;

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {

            cout << C[i][j] << "\t";
        }
        cout << endl;
    }
    history << h << endl;
    history << "\nMatricesA - Matrices B" << endl;
    history << "\nMatrices A : " << endl;
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {

            history << a[i][j] << "\t";
        }
        history << endl;
    }
    history << "\nMatrices B : " << endl;
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {

            history << b[i][j] << "\t";
        }
        history << endl;
    }
    closeAndSave(r, c);
}
/*For calculating Determinant of the Matrix */
float determinant(float a[20][20], int r)
{

    float f = 1, det = 0;
    float b[20][20];
    int m, n, c;
    if (r == 1)
    {
        return (a[0][0]);
    }

    det = 0;
    for (c = 0; c < r; c++)
    {
        m = 0;
        n = 0;
        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < r; j++)
            {
                b[i][j] = 0;
                if (i != 0 && j != c)
                {
                    b[m][n] = a[i][j];
                    if (n < (r - 2))
                        n++;
                    else
                    {
                        n = 0;
                        m++;
                    }
                }
            }
        }
        det = det + f * (a[0][c] * determinant(b, r - 1));
        f = -1 * f;
    }

    return (det);
}

void cofactor(float num[20][20], int f)
{
    float b[20][20], fac[20][20];
    int p, q, m, n, i, j;
    for (q = 0; q < f; q++)
    {
        for (p = 0; p < f; p++)
        {
            m = 0;
            n = 0;
            for (i = 0; i < f; i++)
            {
                for (j = 0; j < f; j++)
                {
                    if (i != q && j != p)
                    {
                        b[m][n] = num[i][j];
                        if (n < (f - 2))
                            n++;
                        else
                        {
                            n = 0;
                            m++;
                        }
                    }
                }
            }
            fac[q][p] = pow(-1, q + p) * determinant(b, f - 1);
        }
    }
    transpose(num, fac, f);
}
/*Finding transpose of matrix*/
void transpose(float num[20][20], float fac[20][20], int r)
{
    int i, j;
    float b[20][20], d;

    for (i = 0; i < r; i++)
    {
        for (j = 0; j < r; j++)
        {
            b[i][j] = fac[j][i];
        }
    }
    d = determinant(num, r);
    for (i = 0; i < r; i++)
    {
        for (j = 0; j < r; j++)
        {
            C[i][j] = b[i][j] / d;
        }
    }
    cout << ("\nThe inverse of matrix is : \n");

    for (i = 0; i < r; i++)
    {
        for (j = 0; j < r; j++)
        {
            cout << C[i][j] << "\t";
        }
        cout << "\n";
    }
    history << h << endl;
    history << "\nInv_MatricesA" << endl;
    history << "\nMatrices A : " << endl;
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < r; ++j) {

            history << num[i][j] << "\t";
        }
        history << endl;
    }

    closeAndSave(r, r);

}
void multiplication(float a[20][20], float b[20][20], int rA, int rB, int cA, int cB)
{
    cout << ("\nThe result of multiplication is : \n"); cout << endl;
    for (int i = 0; i < rA; i++) {
        for (int j = 0; j < cB; j++) {
            C[i][j] = 0;

            for (int k = 0; k < rB; k++) {
                C[i][j] += a[i][k] * b[k][j];
            }
            cout << C[i][j] << "\t";
        }
        cout << endl;
    }
    history << h << endl;
    history << "\nMatricesA * Matrices B" << endl;
    history << "\nMatrices A : " << endl;
    for (int i = 0; i < rA; ++i) {
        for (int j = 0; j < cA; ++j) {

            history << a[i][j] << "\t";
        }
        history << endl;
    }
    history << "\nMatrices B : " << endl;
    for (int i = 0; i < rB; ++i) {
        for (int j = 0; j < cB; ++j) {

            history << b[i][j] << "\t";
        }
        history << endl;
    }
    closeAndSave(cA, rB);

}
void scalar(float a[20][20], int r, int c) {
    float s;
    cout << ("\nEnter the scalar : ");
    cin >> s;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            C[i][j] = s * a[i][j];
        }
    }
    cout << "The result of scalar multiplication: " << endl;

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {

            cout << C[i][j] << "\t";
        }
        cout << endl;
    }
    history << h << endl;
    history << "\nMatricesA * " << s << endl;
    history << "\nMatrices A : " << endl;
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {

            history << a[i][j] << "\t";
        }
        history << endl;
    }

    closeAndSave(r, c);
}
void min_max(float a[20][20], int r, int c)
{
    double max, min;

    max = a[0][0];
    min = a[0][0];

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            if (a[i][j] > max)
            {
                max = a[i][j];


            }
            else if (a[i][j] < min)
            {

                min = a[i][j];
            }

        }
    }
    cout << "\nThe maximum value of the matrix is: " << max << endl;
    cout << "The minimum value of the matrix is: " << min << endl;
    history << h << endl;
    history << "\nMatrices A : " << endl;
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {

            history << a[i][j] << "\t";
        }
        history << endl;
    }
    history << "\nThe maximum value of the matrix is: " << max << endl;
    history << "The minimum value of the matrix is: " << min << endl << endl;
}
void pandN(float a[20][20], int r, int c) {
    float num[20];
    int k = 0, l = 0;
    int totalPositive = 0, totalNegative = 0;
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            num[k] = a[i][j];
            k++;
            l++;
        }
    }
    cout << "The total number in the matrices : " << l << endl;

    do {
        if (num[l - 1] >= 0) {
            totalPositive = totalPositive + 1;
            l--;
        }
        else {
            totalNegative = totalNegative + 1;
            l--;
        }

    } while (l > 0);

    cout << "The total positive number in the matrices A is: " << totalPositive << endl;
    cout << "The total negative numbers in the matrices A is: " << totalNegative << endl;
    history << h << endl;
    history << "\nMatrices A : " << endl;
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {

            history << a[i][j] << "\t";
        }
        history << endl;
    }
    history << "\nThe total positive number in the matrices A is: " << totalPositive << endl;
    history << "The total negative numbers in the matrices A is: " << totalNegative << endl << endl;
}
