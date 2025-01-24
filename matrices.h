#ifndef MATRICES_H
#define MATRICES_H

#include "matrix_control.h"

// Matriz representando um "V" de 'checked'
int checked_pattern[MATRIX_SIZE][MATRIX_SIZE] = {
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1},
    {0, 1, 0, 1, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0}
};

// Matriz representando um "X"
int x_pattern[MATRIX_SIZE][MATRIX_SIZE] = {
    {1, 0, 0, 0, 1},
    {0, 1, 0, 1, 0},
    {0, 0, 1, 0, 0},
    {0, 1, 0, 1, 0},
    {1, 0, 0, 0, 1}
};

// Matrizes representando os números

int number_0[MATRIX_SIZE][MATRIX_SIZE] = {
    {0, 1, 1, 1, 0},
    {0, 1, 0, 1, 0},
    {0, 1, 0, 1, 0},
    {0, 1, 0, 1, 0},
    {0, 1, 1, 1, 0}
};

int number_1[MATRIX_SIZE][MATRIX_SIZE] = {
    {0, 1, 0, 0, 0},
    {0, 0, 0, 1, 0},
    {0, 1, 0, 0, 0},
    {0, 0, 0, 1, 0},
    {0, 1, 0, 0, 0}
};

int number_2[MATRIX_SIZE][MATRIX_SIZE] = {
    {0, 1, 1, 1, 0},
    {0, 1, 0, 0, 0},
    {0, 1, 1, 1, 0},
    {0, 0, 0, 1, 0},
    {0, 1, 1, 1, 0}
};

int number_3[MATRIX_SIZE][MATRIX_SIZE] = {
    {0, 1, 1, 1, 0},
    {0, 0, 0, 1, 0},
    {0, 1, 1, 1, 0},
    {0, 0, 0, 1, 0},
    {0, 1, 1, 1, 0}
};

int number_4[MATRIX_SIZE][MATRIX_SIZE] = {
    {0, 1, 0, 0, 0},
    {0, 0, 0, 1, 0},
    {0, 1, 1, 1, 0},
    {0, 1, 0, 1, 0},
    {0, 1, 0, 1, 0}
};

int number_5[MATRIX_SIZE][MATRIX_SIZE] = {
    {0, 1, 1, 1, 0},
    {0, 0, 0, 1, 0},
    {0, 1, 1, 1, 0},
    {0, 1, 0, 0, 0},
    {0, 1, 1, 1, 0}
};

int number_6[MATRIX_SIZE][MATRIX_SIZE] = {
    {0, 1, 1, 1, 0},
    {0, 1, 0, 1, 0},
    {0, 1, 1, 1, 0},
    {0, 1, 0, 0, 0},
    {0, 1, 1, 1, 0}
};

int number_7[MATRIX_SIZE][MATRIX_SIZE] = {
    {0, 1, 0, 0, 0},
    {0, 0, 0, 1, 0},
    {0, 1, 0, 0, 0},
    {0, 0, 0, 1, 0},
    {0, 1, 1, 1, 0}
};

int number_8[MATRIX_SIZE][MATRIX_SIZE] = {
    {0, 1, 1, 1, 0},
    {0, 1, 0, 1, 0},
    {0, 1, 1, 1, 0},
    {0, 1, 0, 1, 0},
    {0, 1, 1, 1, 0}
};

int number_9[MATRIX_SIZE][MATRIX_SIZE] = {
    {0, 1, 1, 1, 0},
    {0, 0, 0, 1, 0},
    {0, 1, 1, 1, 0},
    {0, 1, 0, 1, 0},
    {0, 1, 1, 1, 0}
};

#endif // MATRICES_H