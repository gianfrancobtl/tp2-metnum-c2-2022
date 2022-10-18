#ifndef __Eigen_H_INCLUDED__
#define __Eigen_H_INCLUDED__

#include "matrix.h"
#include <iostream>

using namespace std;

pair<double, vector<double>> *PowerIteration(Matrix *, int niter, int eps);
pair<vector<double>, vector<vector<double>>> *eigen(Matrix *, int num, int niter, int eps);
vector<double> fillRandomVector(int n);
void normalize(vector<double> &v);
void mult(Matrix A, vector<double> &b);
vector<double> multBis(Matrix A, vector<double> b);
double Vector_X_Vector(vector<double> v, vector<double> w);
Matrix Vector_X_VectorT(vector<double> v, vector<double> w);
Matrix Matrix_minus_Matrix(Matrix A, Matrix B);
Matrix Scalar_X_Matrix(double n, Matrix B);

#endif