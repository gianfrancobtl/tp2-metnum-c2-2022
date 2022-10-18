#include "matrix.h"

#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

// Matriz de n x m
Matrix::Matrix(int _n, int _m) : m(_m), n(_n)
{
    matrix = new double *[n];           // antes n*m
    for (int i = 0; i < n; i++)
    {
        matrix[i] = new double[n]{0.0};
    }
}

Matrix::~Matrix()
{
    for (int i = 0; i < n; i++)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
}

double **Matrix::getMatrix()
{
    return matrix;
}

int Matrix::getN()
{
    return n;
}

int Matrix::getM()
{
    return m;
}

double Matrix::getVal(int x, int y)
{
    if (validIndices(x, y))
        return matrix[x][y];
    else // Si x, y están fuera de rango tira una excepcion
        throw std::out_of_range("Indices are out of bounds");
}

void Matrix::setVal(int x, int y, double val)
{
    if (validIndices(x, y))
        matrix[x][y] = val;
    else // Si x, y están fuera de rango tira una excepcion
        throw std::out_of_range("Indices are out of bounds");
}

bool Matrix::validIndices(int x, int y)
{
    // Si no cumple ninguna de las condiciones previas, es verdadero
    return x < this->getN() && y < this->getM();
}

void Matrix::printM()
{
    int l = 0;
    int i, j;
    int n = this->getN();
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (this->getVal(i, j) == 0)
            {
                cout << this->getVal(i, j);
            }
            else
            {
                cout << this->getVal(i, j);
                l++;
            }
            cout << "\t";
        }
        cout << endl;
    }
}

double *Matrix::mult_mat_vec(Matrix *m, double *b){
    double *result = new double[n]{0.00};
    double temp = 0.00;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            temp = temp + (m->getVal(i, j) * b[j]);
            //cout << "A: " << m->getVal(i, j) << endl;
            //cout << "x: " << b[j] << endl;
        }
        result[i] = temp;
        temp = 0.00;
    }
    return result;
}

double *Matrix::restar_vec(double *a, double *b){
    double *result = new double[n]{0.00};
    for (int i = 0; i < n; i++){
        result[i] = a[i] - b[i];
    }
    return result;
}


double Matrix::norma_2(double *a){
    double sum = 0.00;
    for (int i = 0; i < n; i++){
        sum = sum + double (a[i] * a[i]);
    }
    sum = double (sqrt(sum));
    return sum;
}