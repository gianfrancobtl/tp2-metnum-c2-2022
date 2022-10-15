#include <algorithm>
//#include <chrono>
#include <iostream>
#include "knn.h"
#include "pca.h"

using namespace std;

KNNClassifier::KNNClassifier(unsigned int n_neighbors) {
    this->n_neighbors = n_neighbors;
}

void KNNClassifier::fit(Matrix X, Matrix y)
{
    this->x_train = X;
    this->y_train = y;
}

struct {
	bool operator()  (pair<double, unsigned int> p1, pair<double, unsigned int> p2) 
	const { return p1.first < p2.first; }
} customLess;

Vector KNNClassifier::predict(Matrix X)
{
	auto ret = Vector(X.rows());
	for (unsigned k = 0; k < X.rows(); ++k){
		std::vector<pair<double, unsigned int>> distancias(this->x_train.rows());
		for (unsigned i = 0; i < x_train.rows(); i++) {
        		double distancia =  (X.row(k) - this->x_train.row(i)).norm();
			auto digito = (unsigned int) this->y_train.coeff(i,0);
			distancias[i] = (make_pair(distancia, digito));
		}
		sort(distancias.begin(), distancias.end(),customLess);

		vector<int> ocurrencias(10, 0);
		for (int i=0; i<this->n_neighbors;i++) ocurrencias[distancias[i].second]++;

		ret(k) = distance(ocurrencias.begin(),max_element(ocurrencias.begin(),ocurrencias.end()));
	}
	return ret;
}

