#include <iostream>
#include <random>
#include <iterator>
#include <Eigen/Dense>

using namespace std;
using Eigen::MatrixXd;
using Eigen::VectorXd;

pair<double, VectorXd> powerIteration(MatrixXd, int, double);
pair<VectorXd, MatrixXd> eigen(MatrixXd, int, double);
VectorXd normalize(VectorXd v);
MatrixXd agregarVecAColumna(MatrixXd A, VectorXd v, int col);

pair<double, VectorXd> powerIteration(MatrixXd A, int niter, double eps)
{
    VectorXd b = normalize(VectorXd::Random(A.cols()));

    VectorXd old(A.cols());
    VectorXd new_b(A.cols());

    bool stop = false;

    int i = 0;
    while (i < niter && !stop)
    {
        old = b;
        new_b = normalize(A * b);

        double cosAngle = new_b.dot(old);
        if (((1 - eps) < cosAngle) && cosAngle <= 1)
        {
            stop = true;
        }

        b = new_b;
        i++;
    }

    new_b = A * b;
    double eigenvalue = b.dot(new_b);
    return make_pair(eigenvalue, b);
}

pair<VectorXd, MatrixXd> eigen(MatrixXd A, int niter, double eps)
{
    VectorXd eigenvalues(A.cols());
    MatrixXd AV(A.cols(), A.cols()); // matriz de autovectores por columnas

    double l = 0.00;
    pair<double, VectorXd> temp;

    int i = 0;
    while (i < A.cols())
    {
        temp = powerIteration(A, niter, eps);

        cout << "VECTOR B!!!!!!!!!   " << temp.second << endl;
        cout << "\n"
             << endl;

        l = temp.first;                              // guardo el autovalor
        eigenvalues[i] = l;                          // agrego el autovalor al vector de autovalores
        AV = agregarVecAColumna(AV, temp.second, i); // agrego el autovector a su columna correspondiente en la matriz AV

        cout << "MATRIZ AV!!!!!!!!!   " << temp.second << endl;

        cout << AV << endl;
        MatrixXd AUX_MAT(A.cols(), A.cols());
        AUX_MAT = temp.second * temp.second.transpose();
        AUX_MAT *= l;
        A -= AUX_MAT;

        i++;
    }
    cout << "MATRIZ AV!!!!!!!!!   " << temp.second << endl;

    cout << AV << endl;

    pair<VectorXd, MatrixXd> res = make_pair(eigenvalues, AV);
    return res;
}

VectorXd normalize(VectorXd v)
{
    double sum = 0.00;
    for (int i = 0; i < v.size(); i++)
    {
        sum += double(v[i] * v[i]);
    }
    sum = double(sqrt(sum));

    for (int j = 0; j < v.size(); j++)
    {
        v[j] /= sum;
    }
    return v;
}

MatrixXd agregarVecAColumna(MatrixXd A, VectorXd v, int col)
{
    // Agrega el vector v a la columna i de la matriz A
    for (int i = 0; i < A.cols(); i++)
    {
        A(i, col) = v[i];
    }
    return A;
}