#ifndef __Eigen_H_INCLUDED__
#define __Eigen_H_INCLUDED__

#include <iostream>
#include "matrix.h"
#include <vector>

using namespace std;

// Metodo potencia
pair<double, double*> powerIteration(Matrix*, int, double);

// Deflacion
pair<vector<double>, vector<vector<double>>> *eigen(Matrix *, int, int, double);


//---------- Auxiliares ----------//
void fillRandomVector(double* v, int n);
void normalize(double* v, int n);
double* mult(Matrix* A, double* b);
vector<double> multBis(Matrix *A, vector<double> b);
double dotProduct(double* v, double* w, int n);
Matrix Vector_X_VectorT(vector<double> v, vector<double> w);
Matrix Matrix_minus_Matrix(Matrix A, Matrix B);
Matrix Scalar_X_Matrix(double n, Matrix B);
double* copyVec(double* v, int n);

#endif