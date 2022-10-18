#ifndef __Matrix_H_INCLUDED__ //   #define this so the compiler knows it has been included
#define __Matrix_H_INCLUDED__ //   #define this so the compiler knows it has been included

class Matrix
{
private:
    int m;
    int n;
    double **matrix;

    bool validIndices(int x, int y);

public:
    Matrix(int a, int b);
    ~Matrix();
    int getM();
    int getN();
    double **getMatrix();
    void setVal(int x, int y, double val);
    double getVal(int x, int y);
    void printM();
    double *mult_mat_vec(Matrix *m, double *b);
    double *restar_vec(double *a, double *b);
    double norma_2(double *a);

    // Matriz *copy();
    void gauss(Matrix *m, double *b);
    void restar_fila(Matrix *m, int fila_minuendo, int fila_sustraendo, double *b);
};

#endif
