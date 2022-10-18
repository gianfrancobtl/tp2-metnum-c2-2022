#include <iostream>
#include <random>
#include <iterator>
#include <vector>

#include "eigen.h"

using namespace std;

/* pair<double, double*> powerIteration(Matrix *A, int niter, double eps)
{
    int dim = A->getM();
    double* b = new double[dim];
    fillRandomVector(b, dim);
    normalize(b, dim);
    bool stop = false;

    int i = 0;
    while (i < niter && !stop) {
        double* old = copyVec(b, dim);
        double* new_b = mult(A, b);
        normalize(new_b, dim);
        delete[] b;

        double cosAngle = dotProduct(new_b, old, dim);
        if (((1 - eps) < cosAngle) && cosAngle <= 1)
        {
             stop = true;
        }
        i++;
        double* b = copyVec(new_b, dim);        // b = new_b
        delete[] new_b;
        delete[] old;
        }

    double* new_b = mult(A, b);
    double eigenvalue = dotProduct(b, new_b, dim);
    delete[] new_b;
    return make_pair(eigenvalue, b);
} */


/* pair<vector<double>, vector<vector<double>>> *eigen(Matrix *A, int num, int niter, double eps) // num : dimension matriz A;
{
    vector<double> eigenvalues;
    vector<vector<double>> eigenvectors;

    int k = 0;
    while (k < num)
    {
        std::pair<double, vector<double>> result = *PowerIteration(A, niter, eps);

        double l = result.first;
        vector<double> v = result.second;

        eigenvalues.push_back(l);
        eigenvectors.push_back(v); // trasponer al final
        *A = Matrix_minus_Matrix(*A, Scalar_X_Matrix(l, Vector_X_VectorT(v, v)));
        k++;
    }

    //return make_pair(eigenvalues, eigenvectors);
} */

void fillRandomVector(double* v, int n)
{
    srand((unsigned)time(NULL));
    double a = rand() % 100 + 1;
    for (int i = 0; i < n; i++)
    {
        double b = rand() % 20 + 1;
        v[i] = b;
    }
}

void normalize(double* v, int n)
{
    double sum = 0.00;
    for (int i = 0; i < n; i++)
    {
        sum = sum + double(v[i] * v[i]);
    }
    sum = double(sqrt(sum));

    for (int j = 0; j < n; j++)
    {
        v[j] /= sum;
    }
}

double* mult(Matrix *A, double* b)
{
    int dim = A->getM();
    double *result = new double[dim]{0.00};
    double aux = 0.00;

    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            aux += (A->getVal(i, j) * b[j]);
        }
        result[i] = aux;
        aux = 0.00;
    }
    return result;
}

vector<double> multBis(Matrix *A, vector<double> b)
{
    vector<double> res;
    double aux = 0.00;
    for (int i = 0; i < A->getM(); i++)
    {
        for (int j = 0; j < A->getM(); j++)
        {
            aux += (A->getVal(i, j) * b[j]);
        }
        res.push_back(aux);
        aux = 0.00;
    }
    return res;
}

double dotProduct(double* v, double* w, int n)
{
    double res;
    for (int i = 0; i < n; i++)
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

double* copyVec(double* v, int n){
    double *res = new double[n];
    for (int i = 0; i < n; i++){
        res[i] = v[i];
    }
    return res;
}