#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "matrix.h"
#include "eigen.h"

using namespace std;

Matrix *generarMatrizDesdeArchivo(ifstream &archivoDeEntrada);

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

	Matrix *X = generarMatrizDesdeArchivo(archivoDeEntrada);

	X->printM();
	cout << "2" << endl;

	double eigenvalue;
	/* double *eigenvector = new double[X->getM()];
	Matrix *eigenvectors = new Matrix(X->getM(), X->getM());

	Matrix * mat = new Matrix(2, 2);
	mat->setVal(0, 0, 1);
	mat->setVal(0, 1, 2);
	mat->setVal(1, 0, 2);
	mat->setVal(1, 1, 1);
	mat->printM();
 */
	/* pair<double, double*> res = powerIteration(mat, niter, eps);
	cout << "autovalor: " << res.first << endl;
	cout << "autovector: " << endl;
	for (int i = 0; i < 2; i++){
		cout << "[" << res.second[i] << "], " << endl; 
	} */

	// pair<vector<double>, vector<vector<double>>> res = eigen(X, X->getM(), niter, eps);

	// vector<double> eigenvalues = res.first;

	// for (int k = 0; k < eigenvalues.size(); k++)
	// {
	// 	cout << eigenvalues[k] << endl;
	// }
	delete X;
	return 0;
}

Matrix *generarMatrizDesdeArchivo(ifstream &archivoDeEntrada)
{
	int n = 2;
	int val;
	Matrix *res = new Matrix(n, n);

	if (archivoDeEntrada.is_open())
	{
		cout << "hola" << endl;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				archivoDeEntrada >> val;

				// Seteo del valor 1 a la posición [i][j]:
				res->setVal(i, j, val);
			}
		}
	}

	return res;
} 
