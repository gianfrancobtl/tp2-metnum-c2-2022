#ifndef __Eigen_H_INCLUDED__
#define __Eigen_H_INCLUDED__

#include <iostream>
#include "matrix.h"
#include <vector>

using namespace std;

// Metodo potencia
pair<double, double *> powerIteration(Matrix *, int, double);

// Deflacion
pair<double *, Matrix *> eigen(Matrix *, int, double);

//---------- Auxiliares ----------//
void fillRandomVector(double *v, int n);
void normalize(double *v, int n);

// Multiplico "A" y "b" y los inserto en "v"
void multToVec(double *v, Matrix *A, double *b);

// covariance-matrix-fb.txt
vector<double> multBis(Matrix *A, vector<double> b);
double dotProduct(double *v, double *w, int n);
void vectorMult(Matrix *AUX_MAT, double *v, double *w);
void restaMat(Matrix *A, Matrix *AUX_MAT);
void scalarMult(Matrix *AUX_MAT, double l);
void agregarVecAColumna(Matrix *A, double *v, int col);

// copio el vector w en el vector v sin cambiar los punteros
void copyVec(double *v, double *w, int n);

#endif