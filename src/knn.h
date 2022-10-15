#pragma once
#include "types.h"
#include "pca.h"

class KNNClassifier {
public:
    KNNClassifier(unsigned int n_neighbors);

    void fit(Matrix X, Matrix y);

    Vector predict(Matrix X);
private:
    unsigned int n_neighbors;	// k
    Vector y_train;
    MatrixXd x_train;

};
