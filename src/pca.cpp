#include <iostream>
#include "pca.h"
#include "eigen.h"

using namespace std;

unsigned int N_ITERATIONS = 2000;
double EPSILON = 1e-10;

PCA::PCA(unsigned int n_components){
	this->n_components = n_components;
}

void PCA::fit(Matrix X){
	cout<<"PCA::fit 0"<<endl;
	auto centered = X.rowwise() - X.colwise().mean();
	cout<<"PCA::fit 1"<<endl;
    	Matrix covariance = (centered.transpose() * centered) / double(X.rows() - 1);
	cout<<"PCA::fit 2"<<endl;
	auto eigenpairs = get_first_eigenvalues(covariance, this->n_components,N_ITERATIONS,EPSILON);
	cout<<"PCA::fit 3"<<endl;
	this->P = eigenpairs.second;
}

MatrixXd PCA::transform(Matrix X) {
    return X * P;
}