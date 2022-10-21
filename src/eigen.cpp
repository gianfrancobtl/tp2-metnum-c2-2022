#include <iostream>
#include <random>
#include <iterator>
#include <vector>

#include "eigen.h"

using namespace std;

pair<double, double *> powerIteration(Matrix *A, int niter, double eps)
{
    int dim = A->getM();
    double *b = new double[dim];
    double *old = new double[dim];
    double *new_b = new double[dim];

    fillRandomVector(b, dim);
    normalize(b, dim);
    bool stop = false;

    int i = 0;
    while (i < niter && !stop)
    {
        copyVec(old, b, dim);   // Copio el vector "b" en el vector "old" (old = b)
        multToVec(new_b, A, b); // Multiplico "A" y "b" y los inserto en "new_b"
        normalize(new_b, dim);  // Normalizo "new_b"

        double cosAngle = dotProduct(new_b, old, dim);
        if (((1 - eps) < cosAngle) && cosAngle <= 1)
        {
            stop = true;
        }

        copyVec(b, new_b, dim); // b = new_b
        i++;
    }

    multToVec(new_b, A, b); // new_b = A @ b
    double eigenvalue = dotProduct(b, new_b, dim);
    delete[] old; // elimino los vectores salvo "b" que lo devuelvo (le hago el delete afuera)
    delete[] new_b;
    return make_pair(eigenvalue, b);
}

pair<double *, Matrix *> eigen(Matrix *A, int niter, double eps)
{ //
    int dim = A->getM();

    double *eigenvalues = new double[dim];
    Matrix *AV = new Matrix(dim, dim); // matriz de autovectores por columnas, hay que hacerle delete

    double l = 0.00;
    pair<double, double *> temp;

    int i = 0;
    while (i < dim)
    {
        temp = powerIteration(A, niter, eps); // hay que hacerle delete al res.second (double* creado en powerIteration)

        l = temp.first;                         // guardo el autovalor
        eigenvalues[i] = l;                     // agrego el autovalor al vector de autovalores
        agregarVecAColumna(AV, temp.second, i); // agrego el autovector a su columna correspondiente en la matriz AV

        Matrix *AUX_MAT = new Matrix(dim, dim);
        vectorMult(AUX_MAT, temp.second, temp.second); // Devuelve en AUX_MAT el producto entre los dos vectores
        scalarMult(AUX_MAT, l);                        // Devuelve en AUX_MAT el producto escalar AUX_MAT*l
        restaMat(A, AUX_MAT);                          // Devuelve en A la resta A - AUX_MAT

        delete AUX_MAT;       // delete de la matriz auxiliar creada para hacer las operaciones
        delete[] temp.second; // delete del double* retornado en powerIteration
        i++;
    }

    pair<double *, Matrix *> res = make_pair(eigenvalues, AV);
    return res;
}

void fillRandomVector(double *v, int n)
{
    srand((unsigned)time(NULL));
    double a = rand() % 100 + 1;
    for (int i = 0; i < n; i++)
    {
        double b = rand() % 20 + 1;
        v[i] = b;
    }
}

void normalize(double *v, int n)
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

void multToVec(double *v, Matrix *A, double *b)
{
    int dim = A->getM();
    double aux = 0.00;

    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            aux += (A->getVal(i, j) * b[j]);
        }
        v[i] = aux;
        aux = 0.00;
    }
}

double dotProduct(double *v, double *w, int n)
{
    double res = 0.00;
    for (int i = 0; i < n; i++)
    {
        res += v[i] * w[i];
    }
    return res;
}

void vectorMult(Matrix *AUX_MAT, double *v, double *w_t)
{
    int dim = AUX_MAT->getM();
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            AUX_MAT->setVal(i, j, v[i] * w_t[j]);
        }
    }
}

void restaMat(Matrix *A, Matrix *AUX_MAT)
{
    int dim = A->getM();
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            double new_val = A->getVal(i, j) - AUX_MAT->getVal(i, j);
            A->setVal(i, j, new_val);
        }
    }
}

void scalarMult(Matrix *AUX_MAT, double l)
{
    int dim = AUX_MAT->getM();
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            double new_val = l * (AUX_MAT->getVal(i, j));
            AUX_MAT->setVal(i, j, new_val);
        }
    }
}

void copyVec(double *v, double *w, int n)
{
    for (int i = 0; i < n; i++)
    {
        v[i] = w[i];
    }
}

void agregarVecAColumna(Matrix *A, double *v, int col)
{ // Agrega el vector v a la columna i de la matriz A
    int dim = A->getM();
    for (int i = 0; i < dim; i++)
    {
        A->setVal(i, col, v[i]);
    }
}