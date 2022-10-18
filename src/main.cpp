#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

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

	instance *ins = generarInstanciaDesdeArchivo(archivoDeEntrada);

	Matrix *X = ins->getMatrizDeEntrada();

	X->printM();

	double *respuesta = new double[34];

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
			for (int j = 0; i < n; i++)
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