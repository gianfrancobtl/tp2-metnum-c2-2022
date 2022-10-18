#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "instance.h"
#include "matrix.h"
#include "eigen.h"

using namespace std;

instance *generarInstanciaDesdeArchivo(ifstream &archivoDeEntrada);

// argumentos
// 0 - main.-
// 1 - Matriz: archivo con la matriz de entrada.-
// 2 - iter: cantidad de iteraciones.-
// 3 - eps: tolerancia para la convergencia.-
int main(int argc, char **argv)
{
	cout << "Corriendo el programa..." << endl;

	if (argc != 4)
	{
		cout << "Error, Faltan Argumentos." << endl;
		return 1;
	}

	ifstream archivoDeEntrada(argv[1]);
	int niter = std::stoi(argv[2]);
	double eps = std::stod(argv[3]);

	instance *ins = generarInstanciaDesdeArchivo(archivoDeEntrada);

	Matrix *X = ins->getMatrizDeEntrada();

	// X->printM();
	cout << "2" << endl;

	double eigenvalue;
	double *eigenvector = new double[X->getM()];
	Matrix *eigenvectors = new Matrix(X->getM(), X->getM());

	// pair<double, double[]> *res = PowerIteration(*X, niter, eps);
	cout << "3" << endl;

	// pair<vector<double>, vector<vector<double>>> res = eigen(X, X->getM(), niter, eps);

	// vector<double> eigenvalues = res.first;

	// for (int k = 0; k < eigenvalues.size(); k++)
	// {
	// 	cout << eigenvalues[k] << endl;
	// }

	return 0;
}

instance *generarInstanciaDesdeArchivo(ifstream &archivoDeEntrada)
{
	int n = 34;
	int val;
	Matrix *MatrizDeEntrada = new Matrix(n, n);

	if (archivoDeEntrada.is_open())
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				archivoDeEntrada >> val;

				// Seteo del valor 1 a la posición [i][j]:
				MatrizDeEntrada->setVal(i, j, val);
			}
		}
	}

	// Nueva instancia del resultado;
	// Se setean la matriz W y la cantidad total de links entre las páginas.
	instance *res = new instance();
	res->setMatrizDeEntrada(MatrizDeEntrada);
	return res;
}