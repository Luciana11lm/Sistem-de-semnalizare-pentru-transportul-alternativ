#ifndef MATRIXUTILS_H
#define MATRIXUTILS_H

#include <LedControl.h>

// Funcții pentru matrice
void initializeMatrix(LedControl& matrix);
void displayArrow(int arrow[], LedControl& matrix);
void displayCircle(int circle[], LedControl& matrix);
void clearMatrix(LedControl& matrix);
void blinkArrow(int arrow[], LedControl& matrix);

#endif
