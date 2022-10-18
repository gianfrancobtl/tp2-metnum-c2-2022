#include "instance.h"

// instance::~instance()
// {
//     delete W;
//     delete D;
// }

// Setea la matriz W
void instance::setMatrizDeEntrada(Matrix *_matrizEntrada)
{
    MatrizDeEntrada = _matrizEntrada;
};

Matrix *instance::getMatrizDeEntrada()
{
    return MatrizDeEntrada;
};
