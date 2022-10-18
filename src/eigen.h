#ifndef __Eigen_H_INCLUDED__
#define __Eigen_H_INCLUDED__

#include "matrix.h"
#include <iostream>

using namespace std;

pair<double, vector<double>> *PowerIteration(Matrix *, int niter, int eps);
pair<vector<double>, vector<vector<double>>> *eigen(Matrix *, int num, int niter, int eps);

#endif