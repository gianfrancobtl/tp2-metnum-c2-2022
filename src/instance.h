#ifndef __instance_H_INCLUDED__ //   #define this so the compiler knows it has been included
#define __instance_H_INCLUDED__ //   #define this so the compiler knows it has been included

#include "matrix.h"
#include <iostream>

class instance
{
private:
    Matrix *MatrizDeEntrada;

public:
    ~instance();

    // SETTERS
    void setMatrizDeEntrada(Matrix *);

    // GETTERS
    Matrix *getMatrizDeEntrada();
};

#endif
