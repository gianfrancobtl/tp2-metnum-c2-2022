#pragma once
#include "types.h"

std::pair<double, Vector>
    power_iteration(const Matrix& mat, unsigned num_iter=5000, double eps=1e-16);

std::pair<Eigen::VectorXd, Matrix>
    get_first_eigenvalues(const Matrix& mat, unsigned num, unsigned num_iter=5000, double epsilon=1e-16);
