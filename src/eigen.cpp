#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <iterator>
#include <vector>
#include "eigen.h"
#include "matrix.h"

using namespace std;

pair<double, vector<double>> powerIteration(Matrix A, int niter, int eps)
{
    vector<double> b = fillRandomVector(A.getM());
    normalize(b);
    bool stop = false;

    int i = 0;
    while (i < niter && stop == false)
    {
        vector<double> old = b;
        mult(A, b);
        normalize(b);

        double cosAngle = Vector_X_Vector(b, old);
        if (((1 - eps) < cosAngle) && cosAngle <= 1)
        {
            stop = true;
        }
        i++;
    }
    double eigenvalue = Vector_X_Vector(b, multBis(A, b));

    return make_pair(eigenvalue, b);
}

// num : dimension matriz A;
pair<vector<double>, vector<vector<double>>> eigen(Matrix A, int num, int niter, int eps)
{
    // Matrix A = A;
    vector<double> eigenvalues;
    vector<vector<double>> eigenvectors;

    int k = 0;
    while (k < num)
    {
        std::pair<double, vector<double>> result = powerIteration(A, niter, eps);

        double l = result.first;
        vector<double> v = result.second;

        eigenvalues.push_back(l);
        eigenvectors.push_back(v);
        A = Matrix_minus_Matrix(A, Scalar_X_Matrix(l, Vector_X_VectorT(v, v)));
        k++;
    }

    return make_pair(eigenvalues, eigenvectors);
}

vector<double> fillRandomVector(int n)
{
    vector<double> v;
    srand((unsigned)time(NULL));
    double a = rand() % 100 + 1;
    for (int i = 0; i < n; i++)
    {
        double b = rand() % 20 + 1;
        v.push_back(b);
    }
    return v;
}

void normalize(vector<double> &v)
{
    double sum = 0.00;
    for (int i = 0; i < v.size(); i++)
    {
        sum = sum + double(v[i] * v[i]);
    }
    sum = double(sqrt(sum));

    for (int j = 0; j < v.size(); j++)
    {
        v[j] /= sum;
    }
}

void mult(Matrix A, vector<double> &b)
{
    double aux = 0.00;
    for (int i = 0; i < A.getM(); i++)
    {
        for (int j = 0; j < A.getM(); j++)
        {
            aux += (A.getVal(i, j) * b[j]);
        }
        b[i] = aux;
        aux = 0.00;
    }
}

vector<double> multBis(Matrix A, vector<double> b)
{
    vector<double> res;
    double aux = 0.00;
    for (int i = 0; i < A.getM(); i++)
    {
        for (int j = 0; j < A.getM(); j++)
        {
            aux += (A.getVal(i, j) * b[j]);
        }
        res.push_back(aux);
        aux = 0.00;
    }
    return res;
}

double Vector_X_Vector(vector<double> v, vector<double> w)
{
    double res;
    for (int i = 0; i < v.size(); i++)
    {
        res += v[i] * w[i];
    }
    return res;
}

Matrix Vector_X_VectorT(vector<double> v, vector<double> w)
{
    Matrix *res = new Matrix(v.size(), w.size());
    for (int i = 0; i < v.size(); i++)
    {
        for (int j = 0; j < w.size(); j++)
        {
            res->setVal(i, j, v[i] * w[j]);
        }
    }
    return *res;
}

Matrix Matrix_minus_Matrix(Matrix A, Matrix B)
{
    Matrix *res = new Matrix(A.getM(), A.getM());
    for (int i = 0; i < A.getM(); i++)
    {
        for (int j = 0; j < A.getM(); j++)
        {
            res->setVal(i, j, A.getVal(i, j) - B.getVal(i, j));
        }
    }
    return *res;
}

Matrix Scalar_X_Matrix(double n, Matrix B)
{
    Matrix *res = new Matrix(B.getM(), B.getM());
    for (int i = 0; i < B.getM(); i++)
    {
        for (int j = 0; j < B.getM(); j++)
        {
            res->setVal(i, j, n * B.getVal(i, j));
        }
    }
    return *res;
}