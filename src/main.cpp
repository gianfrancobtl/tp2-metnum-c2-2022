#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "matrix.h"
#include "eigen.h"

using namespace std;

Matrix *generarMatrizDesdeArchivo(ifstream &, int);
int encuentroDimensionMatrizEntrada(ifstream &);

// argumentos
// 0 - main.-
// 1 - Matriz: archivo con la matriz de entrada.-
// 2 - iter: cantidad de iteraciones.-
// 3 - eps: tolerancia para la convergencia.-

// Ejemplo para correr :
// ./tp ../tests/karateclub_matriz.txt 5 0.00001
int main(int argc, char **argv)
{
	if (argc != 4)
	{
		cout << "Error, Faltan Argumentos." << endl;
		return 1;
	}

	cout << "Corriendo el programa..." << endl;

	ifstream archivoDeEntrada(argv[1]);

	// Preparo archivo de salida 1:
	ofstream archivoAutovalores;
	archivoAutovalores.setf(ios::fixed, ios::floatfield);
	archivoAutovalores.precision(6);
	string nombreCarpetaAutovalores = "./";
	nombreCarpetaAutovalores += argv[1];
	nombreCarpetaAutovalores += "_autovalores.out";

	// Preparo archivo de salida 2:
	ofstream archivoAutovectores;
	archivoAutovectores.setf(ios::fixed, ios::floatfield);
	archivoAutovectores.precision(6);
	string nombreCarpetaAutovectores = "./";
	nombreCarpetaAutovectores += argv[1];
	nombreCarpetaAutovectores += "_autovectores.out";

	int niter = std::stoi(argv[2]);
	double eps = std::stod(argv[3]);

	int dim = encuentroDimensionMatrizEntrada(archivoDeEntrada);
	// int dim = 34;

	// Generamos (copiamos) la matriz que dada por archivo.-
	Matrix *X = generarMatrizDesdeArchivo(archivoDeEntrada, dim);

	// Copio la matriz original para que no sufra cambios (mat_copy = mat).-
	Matrix *mat_copy = new Matrix(dim, dim);
	mat_copy->copyMat(X);

	// CORREMOS EL METODO DE LA POTENCIA CON DEFLACION.-
	pair<double *, Matrix *> res = eigen(mat_copy, niter, eps);

	// Delete de la matriz luego de usar la funcion.-
	delete mat_copy;

	// Abro los archivos de salida.-
	archivoAutovectores.open(nombreCarpetaAutovectores);
	archivoAutovalores.open(nombreCarpetaAutovalores);

	// Cargo el archivo con los autovalores.-
	for (int i = 0; i < dim; i++)
	{
		archivoAutovalores << res.first[i] << endl;
	}

	// Cargo el archivo con los autovectores.-
	for (int i = 0; i < dim; i++)
	{
		for (int j = 0; j < dim; j++)
		{
			archivoAutovectores << res.second->getVal(i, j) << ' ';
		}
		archivoAutovectores << endl;
	}

	// Cierro los archivos de salida.-
	archivoAutovalores.close();
	archivoAutovectores.close();

	// Delete de ambas estructuras (double* y Matrix*).-
	delete[](res.first);
	delete (res.second);

	// Delete de la matriz creada.-
	delete X;
	return 0;
}

Matrix *generarMatrizDesdeArchivo(ifstream &archivoDeEntrada, int n)
{
	int val = 0;

	Matrix *res = new Matrix(n, n);

	if (archivoDeEntrada.is_open())
	{
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

int encuentroDimensionMatrizEntrada(ifstream &archivoDeEntrada)
{
	int res = 0;
	std::string line;
	while (std::getline(archivoDeEntrada, line))
	{
		res += 1;
	}
	archivoDeEntrada.clear(); // Clear the eof and fail flags (para volver al inicio)
	archivoDeEntrada.seekg(0);
	return res;
}