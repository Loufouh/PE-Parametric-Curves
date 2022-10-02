//
// Created by Louis Masson on 02/10/2022.
//

#ifndef MODELISATION_TP1_BERSTEIN_H
#define MODELISATION_TP1_BERSTEIN_H

#include <vector>
#include <cmath>
#include "../src/Vec3.h"

extern std::vector<Vec3> BezierCurveByBernstein(const std::vector<Vec3> &controlPoints, long nbU);

extern Vec3 BezierPointByBernstein(const std::vector<Vec3> &controlPoints, float u);

extern float BernsteinPoly(unsigned long n, unsigned long i, float u);

extern unsigned long binomial(unsigned long n, unsigned long k);

extern unsigned long factorial(unsigned long n);

#endif //MODELISATION_TP1_BERSTEIN_H
